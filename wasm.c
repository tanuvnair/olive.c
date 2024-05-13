#include "olive.c"

#define WIDTH 800
#define HEIGHT 600

uint32_t pixels[WIDTH * HEIGHT];
float angle = 0;

void rotate_point(int *x, int *y) {
}

uint32_t *render(float dt)
{
    olivec_fill(pixels, WIDTH, HEIGHT, 0xFF202020);
    {
        int x1 = WIDTH / 2, y1 = HEIGHT / 8;
        int x2 = WIDTH / 8, y2 = HEIGHT / 2;
        int x3 = WIDTH * 7 / 8, y3 = HEIGHT * 7 / 8;
        rotate_point(&x1, &y1);
        rotate_point(&x2, &y2);
        rotate_point(&x3, &y3);

        olivec_fill_triangle(pixels, WIDTH, HEIGHT, x1, y1, x2, y2, x3, y3, 0xFF2020AA);
    }

    return pixels;
}