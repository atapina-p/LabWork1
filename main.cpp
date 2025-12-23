#include "BMPImage.h"
#include <iostream>

int main() {
    std::string filename;
    std::cout << "File name:" << std::endl;
    std::cin >> filename;

    BMPImage img;
    if (!img.load(filename)) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    auto imgCW = img.rotateClockwise();
    imgCW->save("output_cw.bmp");

    auto imgCCW = img.rotateCounterClockwise();
    imgCCW->save("output_ccw.bmp");

    imgCW->gaussianBlur();
    imgCW->save("gaussian_blur.bmp");
    return 0;
}