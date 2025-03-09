#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "bmp.h"

void printBmpInfo(const BMPFile& bmp) {
    std::cout << "Image offset: " << bmp.offset << std::endl;
    std::cout << "Width: " << bmp.width << std::endl;
    std::cout << "Height: " << bmp.height << std::endl;
    std::cout << "Bit Depth: " << bmp.bitDepth << std::endl;
    std::cout << "Row Depth: " << bmp.rowSize << std::endl;
}

bool isValidBmpHeader(const char* header) {
    return header[0] == 'B' && header[1] == 'M';
}

BMPFile readBmpFile(const char* path) {
    std::fstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::cout << "File " << path << " opened successfully" << std::endl;

    char header[54];
    file.read(header, 54);

    if (!isValidBmpHeader(header)) {
        throw std::runtime_error("Invalid BMP file signature");
    }
    std::cout << "Valid BMP file signature" << std::endl;

    BMPFile bmp;
    bmp.offset = *(uint32_t*)&header[10];
    bmp.width = *(uint32_t*)&header[18];
    bmp.height = std::abs(*(int32_t*)&header[22]);
    bmp.bitDepth = *(uint16_t*)&header[28];

    if (bmp.bitDepth == 24) {
        bmp.rowSize = ((bmp.width * 3 + 3) / 4) * 4;
    } else if (bmp.bitDepth == 32) {
        bmp.rowSize = bmp.width * 4;
    } else {
        throw std::runtime_error("Unsupported bit depth");
    }

    bmp.pixelData.resize(bmp.height * bmp.rowSize);

    file.seekg(bmp.offset, std::ios::beg);
    file.read(reinterpret_cast<char*>(bmp.pixelData.data()), bmp.pixelData.size());

    file.close();
    return bmp;
}

void writeBmpFile(BMPFile& bmp, const char* path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    char header[54];
    *(uint32_t*)&header[0] = 0x4D42;
    *(uint32_t*)&header[2] = 54 + bmp.height * bmp.rowSize;
    *(uint32_t*)&header[10] = 54;
    *(uint32_t*)&header[14] = 40;
    *(uint32_t*)&header[18] = bmp.width;
    *(uint32_t*)&header[22] = bmp.height;
    *(uint16_t*)&header[26] = 1;
    *(uint16_t*)&header[28] = bmp.bitDepth;
    *(uint32_t*)&header[30] = 0;
    *(uint32_t*)&header[34] = bmp.height * bmp.rowSize;
    *(uint32_t*)&header[38] = 0;
    *(uint32_t*)&header[42] = 0;
    *(uint32_t*)&header[46] = 0;
    *(uint32_t*)&header[50] = 0;

    file.write(header, 54);
    file.write(reinterpret_cast<char*>(bmp.pixelData.data()), bmp.pixelData.size());

    file.close();
}
