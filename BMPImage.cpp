#include "BMPImage.h"
#include <fstream>
#include <stdexcept>

uint32_t BMPImage::getWidth() const {
    return header.getWidth();
}
uint32_t BMPImage::getHeight() const {
    return header.getHeight();
}

uint32_t BMPImage::calculateRowSize() const {
    uint32_t w = getWidth();
    return ((w * 3 + 3) / 4) * 4;
}

uint32_t BMPImage::calculatePadding() const {
    uint32_t w = getWidth();
    return (4 - (w * 3) % 4) % 4;
}


bool BMPImage::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    if (!header.read(file)) {
        return false;
    }
    uint32_t h = getHeight();
    uint32_t rowSize = calculateRowSize();
    pixelData.assign(rowSize * h, 0);
    file.seekg(header.getDataOffset(), std::ios::beg); //going to proper position
    for (uint32_t y = 0; y < h; y++) {
        uint32_t rowIndex = (h - 1 - y) * rowSize;
        if (!file.read(reinterpret_cast<char*>(&pixelData[rowIndex]), rowSize)) {
            return false;
        }
    }

    return true;
}

bool BMPImage::save(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    if (!header.write(file)) {
        return false;
    }
    uint32_t h = getHeight();
    uint32_t rowSize = calculateRowSize();

    for (uint32_t y = 0; y < h; y++) {
        uint32_t rowIndex =(h - 1 - y) * rowSize;
        if (!file.write(reinterpret_cast<const char*>(&pixelData[rowIndex]), rowSize)) {
            return false;
        }
    }
    return true;
    
}
