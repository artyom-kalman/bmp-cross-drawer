#include <cstdlib>
#include <iostream>
#include "bmp.cpp"
#include "draw.cpp"
#include "display.cpp"

char* getUserInput(const char* prompt) {
    char* input = new char[256];
    std::cout << prompt;
    std::cin >> input;
    return input;
}

int main() {
    const char* inputPath = getUserInput("Enter input BMP file name: ");

    BMPFile bmp = readBmpFile(inputPath);

    printBmpInfo(bmp);

    std::cout << "Original Image" << std::endl;
    displayImage(bmp);

    drawCross(bmp, {{0, 0}, {5, 5}}, {{5, 0}, {0, 5}});
    std::cout << "New Image" << std::endl;
    displayImage(bmp);

    const char* outputPath = getUserInput("Enter output BMP file name: ");
    writeBmpFile(bmp, outputPath);

    return 0;
}
