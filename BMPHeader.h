/*
* Polina Atapina
* st139859@student.spbu.ru
* My labwork 1
*/

#ifndef BMPHEADER
#define BMPHEADER

#include <cstdint>
#include <fstream>
#pragma pack(push, 1)
struct BMPFileHeader
{
    uint16_t fileType;
    uint32_t fileSize; // size of image
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offsetData;
};

struct BMPInfoHeader
{
    uint32_t size; // struct size
    uint32_t width; // struct width
    uint32_t height; // struct height
    uint16_t planes; // plane number(always 1)
    uint16_t bitCount; // 8R + 8G + 8B
    uint32_t compression; // without compression
    uint32_t imageSize; // image data size
    int32_t xPixelsPerMeter;
    int32_t yPixelsPerMeter;
    uint32_t colorsUsed; // color used
    uint32_t colorsImportant; // important colors
};
#pragma pack(pop)

class BMPHeader
{
private:
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    uint32_t rowStride;

public:
    BMPHeader() = default;
    BMPHeader(uint32_t n_width, uint32_t n_height);

    bool read(std::ifstream& file);
    bool write(std::ofstream& file) const;


    uint32_t getWidth() const;
    uint32_t getHeight() const;
    uint32_t getRowStride() const;
    uint32_t getImageDataSize() const;
    uint16_t getBitsPerPixel() const;
    uint32_t getDataOffset() const;

    void setWidth(uint32_t new_width);
    void setHeight(uint32_t new_height);
    void setImageDataSize(uint32_t new_size);
    void setDimensions(uint32_t new_width, uint32_t new_height);
};
#endif