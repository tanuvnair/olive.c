#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include "olive.c"

#define HEIGHT 21
#define WIDTH 21

#define BLACK 0x00000000
#define WHITE 0xFFFFFFFF

static uint32_t pixels[HEIGHT * WIDTH];

void draw_qr_structure()
{
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFFFFEEE00);

    // Top left
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 0, 0, 8, 8, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 0, 0, 7, 7, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 1, 1, 5, 5, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 2, 2, 3, 3, BLACK);

    // Top Right
    olivec_fill_rect(pixels, WIDTH, HEIGHT, WIDTH - 8, 0, 8, 8, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, WIDTH - 7, 0, 7, 7, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, WIDTH - 6, 1, 5, 5, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, WIDTH - 5, 2, 3, 3, BLACK);

    // Bottom Left
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 0, HEIGHT - 8, 8, 8, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 0, HEIGHT - 7, 7, 7, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 1, HEIGHT - 6, 5, 5, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 2, HEIGHT - 5, 3, 3, BLACK);

    // Useless Bit
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 13, 1, 1, BLACK);
    
    // Timing Patterns
    for (int i = 8; i <= 12; i++)
    {
        if (i % 2 == 0)
        {
            olivec_fill_rect(pixels, WIDTH, HEIGHT, i, 6, 1, 1, BLACK);
        }
        else
        {
            olivec_fill_rect(pixels, WIDTH, HEIGHT, i, 6, 1, 1, WHITE);
        }
    }

    for (int i = 8; i <= 12; i++)
    {
        if (i % 2 == 0)
        {
            olivec_fill_rect(pixels, WIDTH, HEIGHT, 6, i, 1, 1, BLACK);
        }
        else
        {
            olivec_fill_rect(pixels, WIDTH, HEIGHT, 6, i, 1, 1, WHITE);
        }
    }

    // Error Correction Level [l - low, m - medium (default), h - high, q - quartile]
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 0, 8, 2, 1, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 19, 1, 2, WHITE);

    char err_correction_level = 'h';

    switch (err_correction_level)
    {
    case 'q':
        olivec_fill_rect(pixels, WIDTH, HEIGHT, 0, 8, 2, 1, BLACK);
        olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 19, 1, 2, BLACK);
        break;
    case 'h':
        olivec_fill_rect(pixels, WIDTH, HEIGHT, 0, 8, 1, 1, BLACK);
        olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 20, 1, 1, BLACK);
        break;
    case 'l':
        olivec_fill_rect(pixels, WIDTH, HEIGHT, 1, 8, 1, 1, BLACK);
        olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 19, 1, 1, BLACK);
        break;
    }

    // Mask
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 2, 8, 3, 1, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 16, 1, 3, WHITE);

    int mask = 1;

    switch (mask)
    {
        case 1:
            // j % 3 mask
            olivec_fill_rect(pixels, WIDTH, HEIGHT, 2, 8, 3, 1, BLACK);
            olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 16, 1, 3, BLACK);
            break;
    }

    // Error Correction
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 5, 8, 1, 1, WHITE);

    olivec_fill_rect(pixels, WIDTH, HEIGHT, 7, 8, 1, 1, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 8, 1, 1, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 7, 1, 1, BLACK);

    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 4, 1, 2, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 3, 1, 1, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 1, 1, 2, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 0, 1, 1, WHITE);

    olivec_fill_rect(pixels, WIDTH, HEIGHT, 13, 8, 1, 1, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 14, 8, 3, 1, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 17, 8, 1, 1, WHITE);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 18, 8, 2, 1, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 20, 8, 1, 1, WHITE);

    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 14, 1, 1, BLACK);
    olivec_fill_rect(pixels, WIDTH, HEIGHT, 8, 15, 1, 1, WHITE);
    
}

bool qr_example(void)
{
    draw_qr_structure();

    const char *file_path = "qr.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err)
    {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }

    return true;
}

int main(void)
{
    if (!qr_example())
        return -1;
    return 0;
}