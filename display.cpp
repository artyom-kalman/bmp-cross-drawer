#include <iostream>
#include <vector>
#include "bmp.h"

void displayImage(const BMPFile& bmp) {
    for (int y = bmp.height - 1; y >= 0; y--) {
        for (int x = 0; x < bmp.width; x++) {
            int pixelIndex = y * bmp.rowSize + x * (bmp.bitDepth / 8);

            if (pixelIndex + 2 >= bmp.pixelData.size()) {
                std::cout << ' ';
                continue;
            }

            int r = bmp.pixelData[pixelIndex + 2];
            int g = bmp.pixelData[pixelIndex + 1];
            int b = bmp.pixelData[pixelIndex];

            int pixel = (r + g + b) / 3;
            std::cout << (pixel < 128 ? " ■ " : " □ ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
