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
    errno olivec_save_to_ppm_file(uint32_t *pixels, size_t width, size_t height, const char *file_path)
    
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
    
    - Iterates through each pixel in the `pixels` array.
    - Extracts the RGB components from the 32-bit pixel value and stores them in `bytes` array.
    - Writes the `bytes` array to the file using `fwrite`.
    - Checks for errors during the write operation.
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

# Important links

[PPM image files (utah.edu)](https://my.eng.utah.edu/~cs5610/ppm.html#:~:text=If%20the%20PPM%20magic%20identifier,carriage%20return%20or%20line%20feed.)