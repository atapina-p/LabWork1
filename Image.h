#ifndef IMAGE
#define IMAGE

#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <memory>

class Image {
public:
    virtual ~Image() = default;

    // чисто виртуальные методы
    virtual bool load(const std::string& filename) = 0; // функция для загрузки изображения
    virtual bool save(const std::string& filename) const = 0; // для сохранения изображения

    // геттеры размеров изображения
    virtual uint32_t getWidth() const = 0;
    virtual uint32_t getHeight() const = 0;

    // virtual std::unique_ptr<Image> rotateCW() const = 0; // вращение по часовой стрелке
    // virtual std::unique_ptr<Image> rotateCCW() const = 0; // против часовой
    

    // virtual std::vector<uint8_t> getPixelData() const = 0; // получение информации о пикселях
    // virtual void setPixelData(const std::vector<uint8_t>& data, uint32_t width, uint32_t height) = 0; // сеттер соответственно
};
#endif