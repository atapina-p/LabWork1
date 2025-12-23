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
    return 0;
}