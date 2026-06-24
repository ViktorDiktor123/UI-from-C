// UI.h
#ifndef UI_H
#define UI_H

// libraries
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// screen array
static uint32_t scr[30] = {0};
static char font_data[2048] = {0};

// create pixel
static inline void pixel(uint8_t x, uint8_t y) {
    if (x < 30 && y < 30) {
        scr[y] |= (1U << x);
    } else {
        printf("pixel error\n");
    }
}

// create rect
static inline void rect(uint8_t r[4], bool full) {
    uint8_t x = r[0];
    uint8_t y = r[1];
    uint8_t w = r[2];
    uint8_t h = r[3];
    if (x + w <= 30 && y + h <= 30) {
        for (uint8_t Y = y; Y < y + h; Y++) {
            for (uint8_t X = x; X < x + w; X++) {
                if (full) {
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

// load font
static inline void font(char file[]) {
    FILE *f = fopen(file, "r"); 
    if (!f) {
        printf("font load error\n");
        return;
    }
    size_t bytes = fread(font_data, 1, sizeof(font_data) - 1, f);
    font_data[bytes] = '\0';
    fclose(f);
}

// output char
static inline void draw_char(char c, uint8_t start_x, uint8_t start_y) {
    if (font_data[0] == '\0') return;
    
    char search_pattern[16];
    snprintf(search_pattern, sizeof(search_pattern), "\"%c\": \"", c);
    
    char *start_pos = strstr(font_data, search_pattern);
    if (!start_pos) return; 
    
    start_pos += strlen(search_pattern);
    
    for (uint8_t row = 0; row < 5; row++) {
        unsigned int mask_val = 0;
        
        char *current_block = start_pos + (row * 6);
        
        if (current_block[0] == '\\' && current_block[1] == '\\') {
            current_block++;
        }
        
        if (sscanf(current_block, "\\u%04x", &mask_val) != 1) {
            if (sscanf(current_block, "u%04x", &mask_val) != 1) {
                continue;
            }
        }

        uint8_t mask = (uint8_t)mask_val;
        
        for (uint8_t col = 0; col < 3; col++) {
            if ((mask & (1 << (2 - col))) != 0) {
                pixel(start_x + col, start_y + row);
            }
        }
    }
}

// output text
static inline void text(char text_str[], uint8_t x, uint8_t y) {
    uint8_t current_x = x;
    size_t length = strlen(text_str);

    for (size_t i = 0; i < length; i++) {
        if (current_x + 3 > 30) break;
        if (y + 5 > 30) break;

        if (text_str[i] != ' ') {
            draw_char(text_str[i], current_x, y);
        }
        
        current_x += 4; 
    }
}

// collide rects
static inline bool colliderect(const uint8_t r1[4], const uint8_t r2[4]) {
    uint8_t x1 = r1[0], x2 = r2[0];
    uint8_t y1 = r1[1], y2 = r2[1];
    uint8_t w1 = r1[2], w2 = r2[2];
    uint8_t h1 = r1[3], h2 = r2[3];
    return ((int)x1 < (int)x2 + w2 &&
        (int)x1 + w1 > (int)x2 &&
        (int)y1 < (int)y2 + h2 &&
        (int)y1 + h1 > (int)y2);
}

//collide point
static inline bool collidepoint(const uint8_t r[4], uint8_t px, uint8_t py) {
    if (r == NULL) {return false;}
    uint8_t rx = r[0];
    uint8_t ry = r[1];
    uint8_t rw = r[2];
    uint8_t rh = r[3];
    return (px >= rx && px < rx + rw &&
            py >= ry && py < ry + rh);
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
