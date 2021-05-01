/*
*****************************************
* Thanks to Siddhartha Shankar Das (Sir *                                                                        *
*****************************************
*/

#include "bitmap_image.hpp"

using namespace std;

int main()
{

    bitmap_image image(500, 300);

    // for(int i=0;i<200;i++){
    //     for(int j=0;j<100;j++){
    //         image.set_pixel(i,j,255,255,0);
    //     }
    //     for(int j=150;j<200;j++){
    //         image.set_pixel(i,j,0,0,255);
    //     }
    // }

    // for(int i=400;i<450;i++){
    //     for(int j=50;j<150;j++){
    //         image.set_pixel(i,j,255,0,0);
    //     }
    //     for(int j=200;j<300;j++){
    //         image.set_pixel(i,j,0,255,255);
    //     }
    // }

    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 300; j++)
        {
            if ((250 - i) * (250 - i) + (150 - j) * (150 - j) <= 90 * 90)
                image.set_pixel(i, j, 255, 0, 0);
            else
                image.set_pixel(i, j, 20, 90, 50);
        }
    }

    image.save_image("test.bmp");
    ;

    return 0;
}
