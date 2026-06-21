// UI.h
#ifndef UI_H
#define UI_H

// libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// screen array
static uint32_t scr[30] = {0};

// create pixel
static inline void pixel(uint8_t x, uint8_t y) {
    if (x < 30 && y < 30) {
        scr[y] |= (1U << x);
    } else {
        printf("pixel error\n");
    }
}

// create rect
static inline void rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, bool fool) {
    if (x + w <= 30 && y + h <= 30) {
        for (uint8_t Y = y; Y < y + h; Y++) {
            for (uint8_t X = x; X < x + w; X++) {
                if (fool) {
                    pixel(X, Y);
                } else {
                    if (X == x || Y == y || X == x + w - 1 || Y == y + h - 1) {
                        pixel(X, Y);
                    }
                }
            }
        }
    } else {
        printf("rect error\n");
    }
}

// draw screen
static inline void draw(void) {
    for (uint8_t y = 0; y < 30; y++) {
        for (uint8_t x = 0; x < 30; x++) {
            if (((scr[y] >> x) & 1) == 1) {
                printf("##");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

// clear data screen
static inline void clear(void) {
    for (uint8_t id = 0; id < 30; id++) {
        scr[id] = 0;
    }
}

#endif // UI_H
