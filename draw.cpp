#include "bmp.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

struct Point {
    uint32_t x;
    uint32_t y;
};

struct Line {
    Point start;
    Point end;
};

const int WHITE = 255;
const int BLACK = 0;

void drawLine(BMPFile& bmp, Point start, Point end) {
    if (start.x > bmp.width || start.y > bmp.height || end.x > bmp.width || end.y > bmp.height) {
        std::cout << "Error: Line coordinates are out of bounds." << std::endl;
        return;
    }

    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (x0 >= 0 && x0 < bmp.width && y0 >= 0 && y0 < bmp.height) {
            uint32_t pixelIndex = y0 * bmp.rowSize + x0 * (bmp.bitDepth / 8);

            int color;
            if (bmp.pixelData[pixelIndex] == 0) {
                color = WHITE;
            } else {
                color = BLACK;
            }

            bmp.pixelData[pixelIndex] = color;
            bmp.pixelData[pixelIndex + 1] = color;
            bmp.pixelData[pixelIndex + 2] = color;
        }

        if (x0 == x1 && y0 == y1) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void drawCross(BMPFile& bmp, Line line1, Line line2) {
    drawLine(bmp, line1.start, line1.end);
    drawLine(bmp, line2.start, line2.end);
}
