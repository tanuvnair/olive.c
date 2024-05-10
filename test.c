#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define STB_IMAGE_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "olive.c"

#define return_defer(value) \
    do                      \
    {                       \
        result = (value);   \
        goto defer;         \
    } while (0)

#define UNUSED(x) (void)(x)

#define UNIMPLEMENTED(message)                                                      \
    do                                                                              \
    {                                                                               \
        fprintf(stderr, "%s:%d: UNIMPLEMENTED: %s\n", __FILE__, __LINE__, message); \
        exit(1);                                                                    \
    } while (0)

#define UNREACHABLE(message)                                                      \
    do                                                                            \
    {                                                                             \
        fprintf(stderr, "%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__, message); \
        exit(1);                                                                  \
    } while (0)

#define WIDTH 128
#define HEIGHT 128

#define TEST_DIR_PATH "./test"

uint32_t pixels[WIDTH * HEIGHT];