#include "BMPHeader.h"
#include <vector>

BMPHeader::BMPHeader(uint32_t n_width, uint32_t n_height){
    fileHeader.fileType = 0x4D42;
    fileHeader.reserved1 = 0;
    fileHeader.reserved2 = 0;
    fileHeader.offsetData = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    infoHeader.size = 40;
    infoHeader.width = static_cast<int32_t>(n_width);
    infoHeader.height = static_cast<int32_t>(n_height);
    infoHeader.planes = 1;
    infoHeader.bitCount = 24;
    infoHeader.compression = 0;
    infoHeader.xPixelsPerMeter = 0;
    infoHeader.yPixelsPerMeter = 0;
    infoHeader.colorsUsed = 0; // color used
    infoHeader.colorsImportant = 0; // important colors
    
    rowStride = ((n_width * 3 + 3) / 4) * 4;
    infoHeader.imageSize = rowStride*n_height;
    fileHeader.fileSize = fileHeader.offsetData + infoHeader.imageSize;
}



uint32_t BMPHeader::getWidth() const{
    return infoHeader.width;
}
uint32_t BMPHeader::getHeight() const{
    return infoHeader.height;
}
uint32_t BMPHeader::getRowStride() const{
    return rowStride;
}
uint32_t BMPHeader::getImageDataSize() const{
    return infoHeader.imageSize;
}
uint16_t BMPHeader::getBitsPerPixel() const{
    return infoHeader.bitCount;
}
uint32_t BMPHeader::getDataOffset() const {
    return fileHeader.offsetData;
}

void BMPHeader::setWidth(uint32_t new_width){
    infoHeader.width = static_cast<uint32_t>(new_width);
}
void BMPHeader::setHeight(uint32_t new_height){
    infoHeader.height = static_cast<uint32_t>(new_height);
}
void BMPHeader::setImageDataSize(uint32_t new_size){
    infoHeader.imageSize = static_cast<uint32_t>(new_size);
}



bool BMPHeader::read(std::ifstream& file){
    if (!file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader)))
        return false;

    if (fileHeader.fileType != 0x4D42)
        return false;

    if (!file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader)))
        return false;

    uint32_t headerEnd = sizeof(BMPFileHeader) + infoHeader.size;
    if (fileHeader.offsetData < headerEnd)
        return false;

    uint32_t extraBytes = fileHeader.offsetData - headerEnd;
    if (extraBytes > 0)
        file.seekg(extraBytes, std::ios::cur);

    return true;
}
bool BMPHeader::write(std::ofstream& file) const{
    if (!file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader)))
        return false;

    if (!file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader)))
        return false;

    uint32_t written = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    if (fileHeader.offsetData < written)
        return false;

    uint32_t padding = fileHeader.offsetData - written;
    if (padding > 0)
    {
        std::vector<char> zeros(padding, 0);
        if (!file.write(zeros.data(), zeros.size()))
            return false;
    }

    return true;
}

void BMPHeader::setDimensions(int32_t new_width, int32_t new_height){
    setWidth(new_width);
    setHeight(new_height);
    uint32_t rowStride = ((new_width * 3 + 3) / 4) * 4;
    setImageDataSize(rowStride * new_height);
    fileHeader.fileSize = fileHeader.offsetData + getImageDataSize();
}

  