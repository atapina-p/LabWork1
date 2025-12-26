/*
* Polina Atapina
* st139859@student.spbu.ru
* My labwork 1
*/

#ifndef BMPIMAGE
#define BMPIMAGE

#include "Image.h"
#include "BMPHeader.h"
#include <string>
#include <vector>

class BMPImage : public Image
{
private:
    BMPHeader header;
    std::vector<uint8_t> pixelData;
    static constexpr uint32_t bitesPerPixel=3;
    static constexpr uint32_t paddingAligment=4;
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
    std::unique_ptr<Image> rotateCounterClockwise() const override;
    void gaussianBlur() override;
};
#endif