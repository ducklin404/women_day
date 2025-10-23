#include <Arduino.h>


void trimAndShift(uint8_t *buffer, int width, int height) {
    int pages = height / 8;
    int halfPages = pages / 2;

    for (int x = 0; x < width; x++) {
        for (int page = 0; page < halfPages; page++) {
            // Current byte
            uint8_t current = buffer[page * width + x];
            // Next byte 
            uint8_t next = 0x00;
            if (page < halfPages - 1) {
                next = buffer[(page + 1) * width + x];
            }
            buffer[page * width + x] = (current >> 1) | ((next & 0x01) << 7);
        }
    }
}


