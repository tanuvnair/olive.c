#ifndef OLIVE_C_
#define OLIVE_C_

#include <stdio.h>
#include <stdint.h>
#include <errno.h>

#define return_defer(value) \
    do                      \
    {                       \
        result = (value);   \
        goto defer;         \
    } while (0)

#define OLIVEC_SWAP(T, a, b) \
    do                       \
    {                        \
        T t = a;             \
        a = b;               \
        b = t;               \
    } while (0)

#define OLIVEC_SIGN(T, x) ((T)(x > 0) - (T)(x < 0))

#define OLIVEC_ABS(T, x) (OLIVEC_SIGN(T, x) * (x))

void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{
    for (size_t i = 0; i < width * height; ++i)
    {
        pixels[i] = color;
    }
}

void olivec_fill_rect(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int x1, int y1, int w, int h, uint32_t color)
{
    int x2 = x1 + OLIVEC_SIGN(int, w) * (OLIVEC_ABS(int, w) - 1);
    if (x1 > x2)
        OLIVEC_SWAP(int, x1, x2);

    int y2 = y1 + OLIVEC_SIGN(int, h) * (OLIVEC_ABS(int, h) - 1);
    if (y1 > y2)
        OLIVEC_SWAP(int, y1, y2);

    for (int y = y1; y <= y2; ++y)
    {
        if (0 <= y && y < (int)pixels_height)
        {
            for (int x = x1; x <= x2; ++x)
            {
                if (0 <= x && x < (int)pixels_width)
                {
                    pixels[y * pixels_width + x] = color;
                }
            }
        }
    }
}

void olivec_fill_circle(uint32_t *pixels, size_t pixels_width, size_t pixels_height, int cx, int cy, size_t r, uint32_t color)
{
    if (r == 0)
        return;

    int x1 = cx - r;
    int x2 = cx + r;
    if (x1 > x2)
        OLIVEC_SWAP(int, x1, x2);

    int y1 = cy - r;
    int y2 = cy + r;
    if (y1 > y2)
        OLIVEC_SWAP(int, y1, y2);

    for (int y = y1; y <= y2; ++y)
    {
        if (0 <= y && y < (int)pixels_height)
        {
            for (int x = x1; x <= x2; ++x)
            {
                if (0 <= x && x < (int)pixels_width)
                {
                    int dx = x - cx;
                    int dy = y - cy;
                    if (dx * dx + dy * dy <= r * r)
                    {
                        pixels[y * pixels_width + x] = color;
                    }
                }
            }
        }
    }
}

void olivec_draw_line(uint32_t *pixels, size_t pixels_width,
                      size_t pixels_height, int x1, int y1, int x2, int y2,
                      uint32_t color)
{
    // Objective is to get the values of k and c, where k represents the slope and c is the y-intercept.
    // y = k*x + c
    // y1 = k*x1 + c -(i)
    // y2 = k*x2 + c -(ii)
    // c = y1 - k*x1 -(iii)

    // After Substituting (iii) in (ii)
    // y2 = k*x2 + y1 - k*x1
    // y2 = k*(x2 - x1) + y1
    // y2 - y1 = k*(x2 - x1)
    /// k = (y2 - y1)/(x2 - x1)

    // c = y1 - k*x1
    // k = (y2 - y1)/(x2 - x1)

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx != 0)
    {
        int c = y1 - dy * x1 / dx;

        if (x1 > x2)
            OLIVEC_SWAP(int, x1, x2);
        for (int x = x1; x <= x2; ++x)
        {
            if (0 <= x && x < (int)pixels_width)
            {
                int sy1 = dy * x / dx + c;
                int sy2 = dy * (x + 1) / dx + c;
                if (sy1 > sy2)
                    OLIVEC_SWAP(int, sy1, sy2);
                for (int y = sy1; y <= sy2; y++)
                {
                    if (0 <= y && y < (int)pixels_height)
                    {
                        pixels[y * pixels_width + x] = color;
                    }
                }
            }
        }
    }
    else
    {
        int x = x1;
        if (0 <= x && x < (int)pixels_width)
        {
            if (y1 > y2)
                OLIVEC_SWAP(int, y1, y2);
            for (int y = y1; y <= y2; ++y)
            {
                if (0 <= y && y < (int)pixels_height)
                {
                    pixels[y * pixels_width + x] = color;
                }
            }
        }
    }
}

#endif // OLIVE_C_