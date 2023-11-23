#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include "olive.c"

// Constants for the image
#define WIDTH 800
#define HEIGHT 600

// Unsigned 32-bit integer which stores the pixels
static uint32_t pixels[HEIGHT * WIDTH];

int main(void)
{
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF0000FF);
    const char *file_path = "output.ppm";

    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return 1;
    }
 
    return 0;
}