/*
* Polina Atapina
* st139859@student.spbu.ru
* My labwork 1
*/

#ifndef IMAGE
#define IMAGE

#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <memory>

class Image
{
public:
    virtual ~Image() = default;

    virtual bool load(const std::string& filename) = 0;
    virtual bool save(const std::string& filename) const = 0;

    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    virtual std::unique_ptr<Image> rotateClockwise() const = 0;
    virtual std::unique_ptr<Image> rotateCounterClockwise() const = 0;
    virtual void gaussianBlur() = 0;

    virtual void getPixelData(uint32_t x, uint32_t y, uint8_t& r, uint8_t& g, uint8_t& b) const = 0;
    virtual void setPixelData(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) = 0;


};
#endif