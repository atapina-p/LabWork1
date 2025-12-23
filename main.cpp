#include "BMPImage.h"
#include <iostream>
// #include "GaussianBlur.h"

int main() {
    BMPImage img;
    if (!img.load("input.bmp")) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    auto imgCW = img.rotateClockwise();
    imgCW->save("output_cw.bmp");

    auto imgCCW = img.rotateCounterClockwise();
    imgCCW->save("output_ccw.bmp");

    // Фильтр Гаусса
    imgCW->gaussianBlur();
    imgCW->save("gaussian_blur.bmp");

    // BMPImage imgBlur;
    // imgBlur.setPixelData(data, w, h);
    // imgBlur.save("output_blur.bmp");

    return 0;
}