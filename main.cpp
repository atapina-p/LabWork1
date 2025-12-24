/*
* Polina Atapina
* st139859@student.spbu.ru
* My labwork 1
*/

#include "BMPImage.h"
#include <iostream>

int main()
{
    std::string filename;
    std::cout << "File name:" << std::endl;
    std::cin >> filename;

    BMPImage img;
    if (!img.load(filename))
    {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    auto imgCW = img.rotateClockwise();
    if (!imgCW->save("output_cw.bmp"))
    {
        std::cerr << "Failed to save output_cw.bmp\n";
        return 1;
    }


    auto imgCCW = img.rotateCounterClockwise();
    if (!imgCCW->save("output_ccw.bmp"))
    {
        std::cerr << "Failed to save output_ccw.bmp\n";
        return 1;
    }


    imgCW->gaussianBlur();
    if (!imgCW->save("gaussian_blur.bmp"))
    {
        std::cerr << "Failed to save gaussian_blur.bmp\n";
        return 1;
    }

    return 0;
}