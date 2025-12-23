#include "BMPImage.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

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

void BMPImage::getPixelData(uint32_t x, uint32_t y, uint8_t& r, uint8_t& g, uint8_t& b) const {
    if (x >= getWidth() || y >= getHeight()){
        throw std::out_of_range("Pixel index out of range");
    }
    uint32_t rowSize = calculateRowSize();
    uint32_t index = y * rowSize + x * 3;
    b = pixelData[index];
    g = pixelData[index+1]; 
    r = pixelData[index+2]; 
}

void BMPImage::setPixelData(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= getWidth() || y >= getHeight()){
        throw std::out_of_range("Pixel index out of range");
    }
    uint32_t rowSize = calculateRowSize();
    uint32_t index = y * rowSize + x * 3;
    pixelData[index] = b;
    pixelData[index+1] = g; 
    pixelData[index+2] = r; 
}

std::unique_ptr<Image> BMPImage::rotateClockwise() const {
    uint32_t width = getWidth();
    uint32_t height = getHeight();

    auto newImage = std::make_unique<BMPImage>(); 
    newImage->header = header;
    newImage->header.setDimensions(height, width);

    uint32_t newRowSize = newImage->calculateRowSize();
    newImage->pixelData.assign(newRowSize * width, 0);

    for (uint32_t y = 0; y < height; y++){
        for (uint32_t x = 0; x < width; x++){
            uint8_t r, g, b;
            getPixelData(x, y, r, g, b);

            uint32_t newX = height - 1 - y;
            uint32_t newY = x;
            newImage->setPixelData(newX, newY, r, g, b);
        }
    }
    return newImage;
}
