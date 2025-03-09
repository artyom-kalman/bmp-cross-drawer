#pragma once
#include <cstdint>
#include <vector>

struct BMPFile {
    uint32_t offset;
    uint32_t width;
    uint32_t height;
    uint16_t bitDepth;
    uint32_t rowSize;
    std::vector<uint8_t> pixelData;
};
