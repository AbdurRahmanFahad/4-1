#include <bits/stdc++.h>

using namespace std;

class point;
class triangle;

int Screen_Width, Screen_Height;
double left_limit_x, bottom_limit_y, front_z, rear_z;

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

triangle triangles[100];

int read_data()
{
    FILE *newfile;

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
            number_of_triangles++;
        }

        fclose(newfile);
    }

    return number_of_triangles;
}

int main()
{

    int number_of_triangles = read_data();

    for (int i = 0; i < number_of_triangles; i++)
    {
        triangles[i].print();
    }

    return 0;
}