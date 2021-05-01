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

    void print()
    {
        for (int i = 0; i < 3; i++)
        {
            cout << points[i].x << " " << points[i].y << " " << points[i].z << endl;
        }
        cout << endl;
    }
};

int main()
{
    FILE *newfile;
    int Screen_Width, Screen_Height;
    double left_limit_x, bottom_limit_y, front_z, rear_z;
    triangle triangles[100];

    newfile = fopen("config.txt", "r");

    if (newfile)
    {
        fscanf(newfile, "%d %d %lf", &Screen_Width, &Screen_Height, &left_limit_x);
        fscanf(newfile, "%lf %lf %lf", &bottom_limit_y, &front_z, &rear_z);

        fclose(newfile);
    }

    newfile = fopen("stage3.txt", "r");

    int number_of_triangles = 0;

    if (newfile)
    {
        while (!feof(newfile))
        {
            for (int i = 0; i < 3; i++)
            {
                double x, y, z;
                fscanf(newfile, "%lf %lf %lf", &x, &y, &z);
                triangles[number_of_triangles].points[i].x = x;
                triangles[number_of_triangles].points[i].y = y;
                triangles[number_of_triangles].points[i].z = z;
            }

            triangles[number_of_triangles].print();
            number_of_triangles++;
        }

        fclose(newfile);
    }

    return 0;
}