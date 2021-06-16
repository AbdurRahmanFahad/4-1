#include <bits/stdc++.h>
using namespace std;

class Point
{
public:
    double x, y, z;

    Point()
    {
        x = y = z = 0.0;
    }

    Point(float a, float b, float c)
    {
        x = a, y = b, z = c;
    }

    Point operator+(Point &p)
    {
        Point res = Point(x + p.x, y + p.y, z + p.z);
        return res;
    }

    Point operator-(Point &p)
    {
        Point res = Point(x - p.x, y - p.y, z - p.z);
        return res;
    }

    Point operator*(double d)
    {
        Point res;
        res.x = x * d, res.y = y * d, res.z = z * d;
        return res;
    }

    friend ostream &operator<<(ostream &os, Point &p)
    {
        os << p.x << " " << p.y << " " << p.z << endl;
        return os;
    }
};

class Light
{
public:
    Point light_pos;
    double color[3];
    Light(){};
    Light(Point pos, double r, double g, double b)
    {
        color[0] = r, color[1] = g, color[2] = b;
        light_pos.x = pos.x, light_pos.y = pos.y, light_pos.z = pos.z;
    }
};

class Object
{
public:
    Point reference_point;
    double height, width, length;
    double color[3];
    double coEfficients[4]; // reflection coefficients
    int shine;

    Object() {}

    virtual void draw() {}
    void setColor(double r, double g, double b)
    {
        color[0] = r, color[1] = g, color[2] = b;
    }

    void setShine(int s)
    {
        shine = s;
    }
    void setCoEfficients(double a, double b, double c, double d)
    {
        coEfficients[0] = a,
        coEfficients[1] = b,
        coEfficients[2] = c,
        coEfficients[3] = d;
    }
};

class Sphere : public Object
{
public:
    Sphere() {}
    Sphere(Point center, double radius)
    {
        reference_point = center;
        length = radius;
    }

    void draw()
    {
        cout << "Drawing Sphere" << endl;
    }
};

class Triangle : public Object
{
public:
    Point p1, p2, p3;

    Triangle() {}

    Triangle(Point a, Point b, Point c)
    {
        p1 = a, p2 = b, p3 = c;
    }

    void draw()
    {
        cout << "Drawing Triangle" << endl;
    }
};

class General : public Object
{

public:
    double A, B, C, D, E, F, G, H, I, J;

    General() {}

    General(Point ref, double l, double w, double h)
    {
        reference_point = ref;
        length = l, width = w, height = h;
    }

    void set_ABCD(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j)
    {
        A = a, B = b, C = c, D = d, E = e, F = f;
        G = g, H = h, I = i, J = j;
    }

    void draw()
    {
        cout << "Drawing General" << endl;
    }
};

class Floor : public Object
{
public:
    Floor() {}

    Floor(double floorWidth, double tileWidth)
    {
        reference_point = Point(-floorWidth / 2, -floorWidth / 2, 0);
        length = tileWidth;
    }

    void draw()
    {
        cout << "drawing Floor" << endl;
    }
};