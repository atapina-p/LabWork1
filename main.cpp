#include "BMPImage.h"
#include <iostream>

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
    return 0;
}