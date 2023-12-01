# olive.c

```c
#ifndef OLIVE_C_
#define OLIVE_C_

#endif // OLIVE_C_
```

1. **`#ifndef`**: Stands for "if not defined." It is a preprocessor directive that checks whether the given identifier has been defined previously in the code.
2. **`OLIVE_C_`**: This is the identifier being checked for definition.
3. **`#define`**: Stands for "define." It is used to define the identifier if it has not been defined before.
4. **`#endif`**: Marks the end of the conditional block. If the identifier is not defined, the code between **`#ifndef`** and **`#endif`** will be included in the compilation.

---

```c
void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for (size_t i = 0; i < width * height; ++i)
    {
        pixels[i] = color;
    }
}
```

1. **`void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)`**: This is the function signature. It declares a function named **`olivec_fill`** that takes four parameters:
    - **`uint32_t *pixels`**: A pointer to an array of unsigned 32-bit integers (assumed to represent pixels).
    - **`size_t width`**: The width of the image (number of pixels in each row).
    - **`size_t height`**: The height of the image (number of rows of pixels).
    - **`uint32_t color`**: The color value you want to fill the pixels with.
2. **`for (size_t i = 0; i < width * height; ++i)`**: This is the beginning of a **`for`** loop that iterates over each element in the 1D array of pixels. It uses a loop variable **`i`** initialized to 0 and increments it on each iteration until it reaches the total number of pixels in the image (**`width * height`**).
3. **`pixels[i] = color;`**: Inside the loop, this line sets the value of the pixel at index **`i`** in the array to the specified color. It uses the loop variable **`i`** to traverse the 1D array as if it were a flattened 2D array.

---

```c
typedef int Errno;
```

The **`typedef`** keyword is used to create a new name (alias) for an existing data type. You are creating a new type named **`Errno`** that is an alias for the existing data type **`int`**.

---

```c
#define return_defer(value) do { result = (value); goto defer; } while (0)
```

1. **`#define return_defer(value)`:** This is a preprocessor directive defining a macro named **`return_defer`**. Macros in C are a way to perform text substitution before the actual compilation process.
2. **`do {result = (value); goto defer; } while (0)`:** This is the body of the macro. It's a **`do-while(0)`** loop, which is a common technique used in macros to create a single statement that acts like a block of code. The loop is executed only once.
3. **`result = (value);`:** This line assigns the value of the parameter **`value`** to a variable named **`result`**. This assumes that **`result`** is declared somewhere in the surrounding code.
4. **`goto defer;`:** This line uses the **`goto`** statement to jump to a label named **`defer`**. The **`defer`** label is expected to be defined elsewhere in the code.
5. **`while (0)`:** This part ensures that the entire block is treated as a single statement, allowing the macro to be used in a way that resembles a function call. The **`while (0)`** construct ensures that the loop runs only once.

---

C function to save an array of pixels in a simple image format known as PPM (Portable Pixmap).

1. **Function Signature:**
    
    ```c
    Errno olivec_save_to_ppm_file(uint32_t *pixels, size_t width, size_t height, const char *file_path)
    
    ```
    
    - The function is named `olivec_save_to_ppm_file`.
    - It takes four parameters:
        - `pixels`: A pointer to an array of 32-bit unsigned integers, representing the pixel data. Each pixel is in the format 0xAABBGGRR, where AA is the alpha channel, BB is blue, GG is green, and RR is red.
        - `width`: The width of the image in pixels.
        - `height`: The height of the image in pixels.
        - `file_path`: The path to the file where the image will be saved.
    - The function returns an `errno` value, which is a global variable used for error reporting in C. It indicates whether the function executed successfully or if an error occurred during execution.
2. **Local Variables:**
    
    ```c
    int result = 0;
    FILE *f = NULL;
    
    ```
    
    - `result` is initialized to 0, it is used in the macro.
    - `f` is a pointer to a `FILE` structure, representing the file that will be opened for writing. It is initially set to `NULL`.
3. **Opening the File:**
    
    ```c
    f = fopen(file_path, "wb");
    if (f == NULL) return_defer(errno);
    
    ```
    
    - It attempts to open the file specified by `file_path` in binary write mode ("wb").
    - If the file cannot be opened (due to `fopen` returning `NULL`), the function returns with an `errno` value indicating the error.
4. **Writing Header Information:**
    
    ```c
    fprintf(f, "P6\n%zu %zu 255\n", width, height);
    if (ferror(f)) return_defer(errno);
    
    ```
    
    - Writes the PPM header to the file, including the image type ("P6"), width, height, and maximum pixel value (255).
    - Checks for any errors during the write operation. If an error occurs, the function returns with an `errno` value.
5. **Writing Pixel Data:**
    
    ```c
    for (size_t i = 0; i < width*height; ++i) {
        // 0xAABBGGRR
        uint32_t pixel = pixels[i];
        uint8_t bytes[3] = {
            (pixel>>(8*0))&0xFF,
            (pixel>>(8*1))&0xFF,
            (pixel>>(8*2))&0xFF,
        };
    
        fwrite(bytes, sizeof(bytes), 1, f);
        if (ferror(f)) return_defer(errno);
    }
    
    ```
    
    1. **`uint32_t pixel = pixels[i];`**: Retrieves the 32-bit pixel value from the **`pixels`** array at the current index **`i`**.
    2. **`uint8_t bytes[3] = { ... };`**: Declares an array of three **`uint8_t`** (8-bit unsigned integer) variables named **`bytes`**. These variables will represent the three color components (blue, green, and red) of the pixel.
    3. The three lines within the array initialization are responsible for extracting the individual color components from the 32-bit pixel value:
        - **`(pixel>>(8*0))&0xFF`**: Shifts the bits of **`pixel`** to the right by 0 bytes (0 bits) and then masks the result with **`0xFF`** (hexadecimal) to keep only the least significant 8 bits. This extracts the blue component.
            1. **`pixel>>(8*0)`**: This shifts the bits of **`pixel`** to the right by 0 bytes, which means no change in the bit position. It essentially retrieves the original value of **`pixel`**.
            2. **`&0xFF`**: This performs a bitwise AND operation with **`0xFF`**. The **`0xFF`** value is a byte with all bits set to 1. The effect of ANDing any value with **`0xFF`** is to keep only the least significant 8 bits of that value and set the higher bits to 0.
        - **`(pixel>>(8*1))&0xFF`**: Shifts the bits of **`pixel`** to the right by 1 byte (8 bits) and then masks the result with **`0xFF`** to extract the green component.
        - **`(pixel>>(8*2))&0xFF`**: Shifts the bits of **`pixel`** to the right by 2 bytes (16 bits) and then masks the result with **`0xFF`** to extract the red component.
6. **Cleanup and Return:**
    
    ```c
    defer:
        if (f)
            fclose(f);
        return 0;
    
    ```
    
    - The `defer` label is a common C idiom for cleanup code that is executed before returning from the function, regardless of where the return occurs.
    - Closes the file using `fclose`.
    - Returns 0, indicating successful execution.

---

```c
void olivec_fill_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int x0, int y0, size_t w, size_t h, uint32_t color) {
    for (int dy = 0; dy < (int) h; ++dy) {
        int y = y0 + dy;
        if (y >= 0 && y < (int) pixels_height) {
            for (int dx = 0; dx < (int) w; ++dx) {
                int x = x0 + dx;
                if (x >= 0 && x < (int) pixels_width) {
                    pixels[y*pixels_width + x] = color;
                }
            }
        }
    }
}
```

1. **Outer Loop (`dy`):**
    - The outer loop iterates over the rows of the rectangle. It uses **`dy`** as the offset in the y-direction.
    - **`for (int dy = 0; dy < (int) h; ++dy)`**: This loop ensures that we iterate through each row of the rectangle.
2. **Calculating Current Y-coordinate (`y`):**
    - **`int y = y0 + dy;`**: Calculates the current y-coordinate within the rectangle. **`y0`** is the starting y-coordinate, and **`dy`** is the offset within the rectangle.
3. **Checking Y-coordinate Bounds:**
    - **`if (y >= 0 && y < (int) pixels_height)`**: Ensures that the calculated y-coordinate is within the height of the pixel array. This check prevents accessing pixels outside the vertical bounds of the image.
4. **Inner Loop (`dx`):**
    - The inner loop iterates over the columns of the rectangle. It uses **`dx`** as the offset in the x-direction.
    - **`for (int dx = 0; dx < (int) w; ++dx)`**: This loop ensures that we iterate through each column of the rectangle.
5. **Calculating Current X-coordinate (`x`):**
    - **`int x = x0 + dx;`**: Calculates the current x-coordinate within the rectangle. **`x0`** is the starting x-coordinate, and **`dx`** is the offset within the rectangle.
6. **Checking X-coordinate Bounds:**
    - **`if (x >= 0 && x < (int) pixels_width)`**: Ensures that the calculated x-coordinate is within the width of the pixel array. This check prevents accessing pixels outside the horizontal bounds of the image.
7. **Setting Pixel Color:**
    - **`pixels[y * pixels_width + x] = color;`**: Sets the color of the pixel at the current (x, y) coordinate to the specified **`color`**. The calculation of the index **`y * pixels_width + x`** is used to convert the two-dimensional coordinates (x, y) into the corresponding one-dimensional index in the pixel array.
    - Explanation with example
        
        The expression **`pixels[y * pixels_width + x]`** is used to map a two-dimensional coordinate **`(x, y)`** to a one-dimensional index in the **`pixels`** array.
        
        Suppose you have a pixel array that looks like this:
        
        ```markdown
          0   1   2   3   4     <-- Columns (x)
        ---------------------
        | 3 | 1 | 2 | 6 | 5 |  <-- Row 0 (y)
        ---------------------
        | 6 | 3 | 8 | 9 | 4 |  <-- Row 1 (y)
        ---------------------
        ```
        
        Now, let's say you want to access the pixel at coordinates **`(3, 1)`**. In this case:
        
        - **`x`** is 3 (column index).
        - **`y`** is 1 (row index).
        
        The expression **`y * pixels_width + x`** calculates the one-dimensional index value in the flattened array:

# example.c

```c
static uint32_t pixels[HEIGHT*WIDTH];
```

The line **`static uint32_t pixels[HEIGHT*WIDTH];`** declares a static 1D array of unsigned 32-bit integers named **`pixels`**. The size of this array is determined by multiplying the constants **`HEIGHT`** and **`WIDTH`**.

- **`static`**: This keyword, when used at the global scope, gives the variable internal linkage, meaning it is only visible within the translation unit (source file) where it is defined.
- **`uint32_t`**: This is the data type of each element in the array. **`uint32_t`** represents an unsigned 32-bit integer.
- **`pixels`**: This is the name of the array.
- **`[HEIGHT * WIDTH]`**: This specifies the size of the array. The number of elements is equal to the product of **`HEIGHT`** and **`WIDTH`**. It's important to note that this is a flattened representation of a 2D array, where the elements are arranged sequentially as if the 2D array has been "flattened" into a single dimension.

For example, if **`HEIGHT`** is 600 and **`WIDTH`** is 800, then the array **`pixels`** will have a size of **`600 * 800 = 480,000`** elements.

---

```c
bool checker_example(void) {
    // Step 1: Fill the entire image with a background color
    olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

    // Step 2: Create a checkerboard pattern
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            uint32_t color = BACKGROUND_COLOR;
            if ((x + y) % 2 == 0) {
                // Set an alternate color for cells with even x+y coordinates
                color = 0xFF2020FF;  // This is a shade of blue
            }
            // Fill each cell with the determined color
            olivec_fill_rect(pixels, WIDTH, HEIGHT, x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, color);
        }
    }

    // Step 3: Save the resulting image to a PPM file
    const char *file_path = "checker.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);

    // Step 4: Check for errors in saving the file
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\\n", file_path, strerror(errno));
        return false;
    }

    // Step 5: Return true to indicate success
    return true;
}

```

Explanation:

1. **Background Fill:**
    - `olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);`: Fills the entire image (represented by `pixels`) with the specified background color.
2. **Checkerboard Pattern:**
    - The nested loops iterate over each cell in the checkerboard pattern.
    - `uint32_t color = BACKGROUND_COLOR;`: Initializes the color to the background color.
    - `(x + y) % 2 == 0`: Checks if the sum of `x` and `y` is even. If true, it sets an alternate color (a shade of blue) for cells with even coordinates.
    - `olivec_fill_rect(pixels, WIDTH, HEIGHT, x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, color);`: Fills each cell with the determined color.
3. **Save to PPM File:**
    - `const char *file_path = "checker.ppm";`: Specifies the file path for saving the image.
    - `Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);`: Calls the function to save the image to a PPM file.
4. **Error Handling:**
    - Checks for errors in saving the file using the `Errno` type (assuming it's an error code).
    - Prints an error message if saving fails and returns `false` to indicate failure.
5. **Success Indicator:**
    - If everything succeeds, the function returns `true` to indicate success.

The overall purpose is to generate a checkerboard pattern, save it to a PPM file, and handle any errors that may occur during the process.

---

# Important links

[PPM image files (utah.edu)](https://my.eng.utah.edu/~cs5610/ppm.html#:~:text=If%20the%20PPM%20magic%20identifier,carriage%20return%20or%20line%20feed.)