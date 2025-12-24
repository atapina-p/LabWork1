/*
* Polina Atapina
* st139859@student.spbu.ru
* My labwork 1
*/

#include <gtest/gtest.h>
#include "BMPImage.h"


TEST(BMPImageTest, LoadSaveTest)
{
    BMPImage image;
    EXPECT_TRUE(image.load("test.bmp"));
    EXPECT_TRUE(image.save("copytest.bmp"));
}

TEST(BMPImageTest, RotateClockWise)
{
    BMPImage image;
    image.load("test.bmp");
    uint32_t width = image.getWidth();
    uint32_t height = image.getHeight();
    auto img_cw = image.rotateClockwise();
    EXPECT_EQ(img_cw->getWidth(), height);
    EXPECT_EQ(img_cw->getHeight(), width);
}


TEST(BMPImageTest, RotateCounterClockWise)
{
    BMPImage image;
    image.load("test.bmp");
    uint32_t width = image.getWidth();
    uint32_t height = image.getHeight();
    auto img_ccw = image.rotateCounterClockwise();
    EXPECT_EQ(img_ccw->getWidth(), height);
    EXPECT_EQ(img_ccw->getHeight(), width);
}

TEST(BMPImageTest, ApplyGaussianFilter)
{
    BMPImage image;
    image.load("test.bmp");

    auto img_ccw = image.rotateCounterClockwise();
    auto old_img = image.rotateCounterClockwise();
    img_ccw->gaussianBlur();
    EXPECT_TRUE(img_ccw->save("test1.bmp"));
    EXPECT_TRUE(old_img->save("test0.bmp"));
    uint32_t width = img_ccw->getWidth();
    uint32_t height = img_ccw->getHeight();
    bool changed = false;
    for(uint32_t y=0; y<height; y++)
    {
        for(uint32_t x=0; x<width; x++)
        {
            uint8_t r, g, b;
            img_ccw->getPixelData(x, y, r, g, b);
            uint8_t oldr, oldg, oldb;
            old_img->getPixelData(x, y, oldr, oldg, oldb);
            if(r!=oldr || g!=oldg || b!=oldb)
            {
                changed = true;
                break;
            }
        }
        if(changed) break;
    }

    EXPECT_TRUE(changed);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}