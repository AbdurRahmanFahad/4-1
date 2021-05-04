#include <bits/stdc++.h>
#include "bitmap_image.hpp"

using namespace std;

class point;
class triangle;

int number_of_triangles;
int Screen_Width, Screen_Height;
double left_limit_x, bottom_limit_y, front_z, rear_z;
double right_limit_x, top_limit_y;
double dx, dy, Top_Y, Left_X;

double **z_buffer;
point **frame_buffer;

class point
{
public:
    double x, y, z;

    point()
    {
        x = y = z = 0.0;
    }

    point(float a, float b, float c)
    {
        x = a, y = b, z = c;
    }

    point operator-(point &p)
    {
        point res = point(x - p.x, y - p.y, z - p.z);
        return res;
    }
};

class plane
{
public:
    double a, b, c, d;
};

class triangle
{
public:
    point points[3];
    plane plane;
    int r, g, b;
    double x_max, x_min, y_max, y_min;
    double upper_scanline, lower_scanline;

    void print()
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

    void calculate_plane()
    {
        point AB, AC;
        AB = points[1] - points[0];
        AC = points[2] - points[0];

        point norm = cross(AB, AC);
        plane.a = norm.x;
        plane.b = norm.y;
        plane.c = norm.z;
        plane.d = -(dot(norm, points[0]));
    }

    double get_z(double x, double y)
    {
        return (plane.a * x + plane.b * y + plane.d) / (-plane.c);
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
        triangles[i].calculate_plane();
    }
}

void init_z_buffer()
{
    z_buffer = new double *[Screen_Height];

    for (int i = 0; i < Screen_Height; i++)
    {
        z_buffer[i] = new double[Screen_Width];

        for (int j = 0; j < Screen_Width; j++)
        {
            z_buffer[i][j] = rear_z;
        }
    }
}

void init_frame_buffer()
{
    frame_buffer = new point *[Screen_Height]; //point for storing RGB values

    for (int i = 0; i < Screen_Height; i++)
    {
        frame_buffer[i] = new point[Screen_Width];

        for (int j = 0; j < Screen_Width; j++)
        {
            frame_buffer[i][j].x = 0.0; // r
            frame_buffer[i][j].y = 0.0; // g
            frame_buffer[i][j].z = 0.0; // b
        }
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

point cross(point a, point b)
{
    point res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

double dot(point p1, point p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

void create_image()
{
    bitmap_image output(Screen_Width, Screen_Height);

    for (int i = 0; i < Screen_Width; i++)
    {
        for (int j = 0; j < Screen_Height; j++)
        {
            output.set_pixel(i, j, frame_buffer[i][j].x, frame_buffer[i][j].y, frame_buffer[i][j].z);
        }
    }

    output.save_image("out.bmp");
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