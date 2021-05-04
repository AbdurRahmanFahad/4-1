#include <bits/stdc++.h>

using namespace std;

class point;
class triangle;

int number_of_triangles;
int Screen_Width, Screen_Height;
double left_limit_x, bottom_limit_y, front_z, rear_z;
double right_limit_x, top_limit_y;
double dx, dy, Top_Y, Left_X;

class point
{
public:
    double x, y, z;
};

class triangle
{
public:
    point points[3];
    int r, g, b;
    double x_max, x_min, y_max, y_min;
    double upper_scanline, lower_scanline;

    void
    print()
    {
        for (int i = 0; i < 3; i++)
        {
            cout << points[i].x << " " << points[i].y << " " << points[i].z << endl;
        }
        cout << endl;
    }

    void init()
    {
        r = rand() % 256;
        g = rand() % 256;
        b = rand() % 256;

        x_max = maxx(points[0].x, points[1].x, points[2].x);
        x_min = minn(points[0].x, points[1].x, points[2].x);
        y_max = maxx(points[0].y, points[1].y, points[2].y);
        y_min = minn(points[0].y, points[1].y, points[2].y);

        upper_scanline = y_max < top_limit_y ? y_max : top_limit_y;
        lower_scanline = y_min > bottom_limit_y ? y_min : bottom_limit_y;
    }
};

triangle triangles[100];

void read_data()
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

    number_of_triangles = 0;

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
}

void init_variables()
{
    right_limit_x = -left_limit_x;
    top_limit_y = -bottom_limit_y;

    dx = (right_limit_x * 2) / Screen_Width;
    dy = (top_limit_y * 2) / Screen_Height;

    Top_Y = top_limit_y - dy / 2.0;
    Left_X = left_limit_x + dx / 2.0;

    for (int i = 0; i < number_of_triangles; i++)
    {
        triangles[i].init();
    }
}

double maxx(double a, double b, double c)
{
    return max(max(a, b), c);
}

double minn(double a, double b, double c)
{
    return min(min(a, b), c);
}

int main()
{

    read_data();

    for (int i = 0; i < number_of_triangles; i++)
    {
        triangles[i].print();
    }

    return 0;
}