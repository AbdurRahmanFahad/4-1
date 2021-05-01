#include <bits/stdc++.h>

using namespace std;

class point
{
public:
    double x, y, z;
};

class triangle
{
public:
    point points[3];
    int color[3];
};

int main()
{
    FILE *newfile;
    int Screen_Width, Screen_Height;
    double left_limit_x, bottom_limit_y, front_z, rear_z;

    newfile = fopen("config.txt", "r");

    if (newfile)
    {
        fscanf(newfile, "%d %d %lf", &Screen_Width, &Screen_Height, &left_limit_x);
        fscanf(newfile, "%lf %lf %lf", &bottom_limit_y, &front_z, &rear_z);

        fclose(newfile);
    }

        return 0;
}