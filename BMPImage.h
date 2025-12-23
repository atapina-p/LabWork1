#ifndef BMPIMAGE
#define BMPIMAGE

#include "Image.h"
#include "BMPHeader.h"
#include <string>
#include <vector>

class BMPImage : public Image {
private:
    BMPHeader header;
    std::vector<uint8_t> pixelData;
    uint32_t calculateRowSize() const;
    uint32_t calculatePadding() const;

public:
    BMPImage() = default;

    bool load(const std::string& filename) override;
    bool save(const std::string& filename) const override;

    uint32_t getWidth() const override;
    uint32_t getHeight() const override;
    
    // std::vector<uint8_t> getPixelData() const override;
    // void setPixelData(const std::vector<uint8_t>& data, uint32_t width, uint32_t height) override;

    // void rotateClockwise();
    // void rotateCounterClockwise();
};
#endif