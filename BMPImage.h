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
    
    void getPixelData(uint32_t x, uint32_t y, uint8_t& r, uint8_t& g, uint8_t& b) const override;
    void setPixelData(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) override;

    std::unique_ptr<Image> rotateClockwise() const override;
    // std::unique_ptr<Image> void rotateCounterClockwise() const override;
};
#endif