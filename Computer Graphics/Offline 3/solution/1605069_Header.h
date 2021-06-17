#include <bits/stdc++.h>
#include <windows.h>
#include <glut.h>

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

    void Normalize()
    {
        double modulas = sqrt(x * x + y * y + z * z);
        x = x / modulas, y = y / modulas, z = z / modulas;
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

    void draw()
    {
        glPushMatrix();
        glTranslated(light_pos.x, light_pos.y, light_pos.z);
        glColor3f(color[0], color[1], color[2]);
        glutSolidSphere(2, 100, 100);
        glPopMatrix();
    }
};

class Ray
{
public:
    Point start, dir;

    Ray() {}

    Ray(Point source, Point direction)
    {
        start = source, dir = direction;
        dir.Normalize();
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

    virtual double intersect(Ray *r, double *color, int level)
    {
        return -1.0;
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
        //cout << "Drawing Sphere" << endl;

        glPushMatrix();
        glTranslated(reference_point.x, reference_point.y, reference_point.z);
        glColor3f(color[0], color[1], color[2]);
        glutSolidSphere(length, 100, 100);
        glPopMatrix();
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
        //cout << "Drawing Triangle" << endl;
        glBegin(GL_TRIANGLES);
        glColor3f(color[0], color[1], color[2]);
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p3.x, p3.y, p3.z);
        glEnd();
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
        //cout << "Drawing General" << endl;
    }
};

class Floor : public Object
{
public:
    int no_tiles;

    Floor() {}

    Floor(int floorWidth, int tileWidth)
    {
        reference_point = Point(-floorWidth / 2, -floorWidth / 2, 0);
        length = tileWidth;
        no_tiles = floorWidth / tileWidth;
    }

    void draw()
    {
        //cout << "drawing Floor" << endl;
        double p = reference_point.x;
        double q = reference_point.y;
        double r = reference_point.z;
        glBegin(GL_QUADS);
        {
            for (int i = 0; i < no_tiles; i++)
            {
                for (int j = 0; j < no_tiles; j++)
                {
                    int c = (i + j) % 2;
                    glColor3f(c, c, c);

                    glVertex3f(p + i * length, q + j * length, r);
                    glVertex3f(p + i * length, q + (j + 1) * length, r);
                    glVertex3f(p + (i + 1) * length, q + (j + 1) * length, r);
                    glVertex3f(p + (i + 1) * length, q + j * length, r);
                }
            }
        }
        glEnd();
    }
};