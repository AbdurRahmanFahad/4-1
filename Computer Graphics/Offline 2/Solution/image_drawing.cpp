/*
*****************************************
* Thanks to Siddhartha Shankar Das (Sir *                                                                        *
*****************************************
*/

#include "bitmap_image.hpp"

using namespace std;

int main()
{

    bitmap_image image(500, 500);

    int p = 0;
    for (int i = 0; i < 500; i++)
    {
        for (int j = 0; j < 500; j++)
        {
            double q = (250 - i) * (250 - i) + (250 - j) * (250 - j);
            q = q / (350.0 * 350.0);
            q = (255 - q) * 250.0;
            image.set_pixel(i, j, (int)q, 0, 0);
        }
    }

    image.save_image("test.bmp");

    return 0;
}
