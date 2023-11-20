# example.c

```c
static uint32_t pixels[HEIGHT*WIDTH];
```

The line **`static uint32_t pixels[HEIGHT * WIDTH];`** declares a static 1D array of unsigned 32-bit integers named **`pixels`**. The size of this array is determined by multiplying the constants **`HEIGHT`** and **`WIDTH`**. Here's a breakdown:

- **`static`**: This keyword, when used at the global scope, gives the variable internal linkage, meaning it is only visible within the translation unit (source file) where it is defined.
- **`uint32_t`**: This is the data type of each element in the array. **`uint32_t`** represents an unsigned 32-bit integer.
- **`pixels`**: This is the name of the array.
- **`[HEIGHT * WIDTH]`**: This specifies the size of the array. The number of elements is equal to the product of **`HEIGHT`** and **`WIDTH`**. It's important to note that this is a flattened representation of a 2D array, where the elements are arranged sequentially as if the 2D array has been "flattened" into a single dimension.

For example, if **`HEIGHT`** is 600 and **`WIDTH`** is 800, then the array **`pixels`** will have a size of **`600 * 800 = 480,000`** elements.

```c
void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for (size_t i = 0; i < width*height; ++i) {
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

# PPM Image format:

[PPM image files (utah.edu)](https://my.eng.utah.edu/~cs5610/ppm.html#:~:text=If%20the%20PPM%20magic%20identifier,carriage%20return%20or%20line%20feed.)

```c
#define return_defer(value) do {result = (value); goto defer; } while (0)
```

1. **`#define return_defer(value)`:** This is a preprocessor directive defining a macro named **`return_defer`**. Macros in C are a way to perform text substitution before the actual compilation process.
2. **`do {result = (value); goto defer; } while (0)`:** This is the body of the macro. It's a **`do-while(0)`** loop, which is a common technique used in macros to create a single statement that acts like a block of code. The loop is executed only once.
3. **`result = (value);`:** This line assigns the value of the parameter **`value`** to a variable named **`result`**. This assumes that **`result`** is declared somewhere in the surrounding code.
4. **`goto defer;`:** This line uses the **`goto`** statement to jump to a label named **`defer`**. The **`defer`** label is expected to be defined elsewhere in the code.
5. **`while (0)`:** This part ensures that the entire block is treated as a single statement, allowing the macro to be used in a way that resembles a function call. The **`while (0)`** construct ensures that the loop runs only once.

```c
typedef int Errno;
```

In C programming, the **`typedef`** keyword is used to create a new name (alias) for an existing data type. You are creating a new type named **`Errno`** that is an alias for the existing data type **`int`**.