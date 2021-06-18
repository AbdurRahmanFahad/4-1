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

double Dot_product(Point a, Point b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point Cross_product(Point v1, Point v2)
{
    Point res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;

    return res;
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

    virtual double intersect(Ray r, double *color, int level)
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

    double get_t(Ray ray)
    {
        // P(t) = Ro + t*Rd
        // (Ro + tRd) · (Ro + tRd) - r2  =  0

        Point R0, Rd;
        R0 = ray.start, Rd = ray.dir;
        R0 = R0 - reference_point;

        //  Rd·Rdt2 + 2Rd·Rot + Ro·Ro - r2  =  0
        // at2 + bt + c = 0

        double a, b, c, d, t1, t2;
        a = 1.0;
        b = 2 * Dot_product(R0, Rd);
        c = Dot_product(R0, R0) - length * length;

        d = b * b - 4 * a * c;

        if (a == 0)
            return -c / b;

        if (d < 0) // imaginary value
            return -1;

        d = sqrt(d);
        t1 = (-b + d) / (2 * a);
        t2 = (-b - d) / (2 * a);

        // return closest
        return min(t1, t2);
    }

    double intersect(Ray r, double *clr, int level)
    {
        double t = get_t(r);

        if (t < 1 || t > 1000)
            return -1;

        if (level == 0)
            return t;

        //  Adding Ambient light
        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];

        // TODO: onek kaj korte hobe
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

    double get_t(Ray ray)
    {
        // From wikipedia - Möller–Trumbore intersection algorithm

        Point line_1, line_2;
        line_1 = p2 - p1;
        line_2 = p3 - p1;

        Point h = Cross_product(ray.dir, line_2);

        double check = Dot_product(h, line_1);

        // Checking if parallel
        if (check > -0.0000001 && check < 0.0000001)
            return -1;

        double f = 1.0 / check;
        Point s = ray.start - p1;
        double u = f * Dot_product(s, h);

        if (u < 0.0 || u > 1.0)
            return -1;

        Point q = Cross_product(s, line_1);
        double v = f * Dot_product(ray.dir, q);

        if (v < 0.0 || u + v > 1.0)
            return -1;

        float t = f * Dot_product(line_2, q);

        if (t > 0.0000001) // ray intersection
            return t;
        else // This means that there is a line intersection but not a ray intersection.
            return -1;
    }

    double intersect(Ray r, double *clr, int level)
    {

        double t = get_t(r);

        if (t < 1 || t > 1000)
            return -1;

        if (level == 0)
            return t;

        //  Adding Ambient light
        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];

        // intersection point  (R0 + t * Rd)
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

    double get_t(Ray ray)
    {
        //return -1;
        double Aq, Bq, Cq;
        Point R0 = ray.start, Rd = ray.dir;
        // - reference
        double xo = R0.x, yo = R0.y, zo = R0.z;
        double xd = Rd.x, yd = Rd.y, zd = Rd.z;

        Aq = A * xd * xd + B * yd * yd + C * zd * zd;
        Aq += D * xd * yd + E * xd * zd + F * yd * zd;
        Bq = 2 * A * xo * xd + 2 * B * yo * yd + 2 * C * zo * zd;
        Bq += D * (xo * yd + yo * xd) + E * (xo * zd + zo * xd) + F * (yo * zd + yd * zo);
        Bq += G * xd + H * yd + I * zd;
        Cq = A * xo * xo + B * yo * yo + C * zo * zo + D * xo * yo;
        Cq += E * xo * zo + F * yo * zo + G * xo + H * yo + I * zo + J;

        double t1, t2, dd;
        dd = Bq * Bq - 4 * Aq * Cq;

        if (Aq == 0)
            return -Cq / Bq;

        if (dd < 0)
            return -1;

        dd = sqrt(dd);

        t1 = (-Bq - dd) / (2 * Aq);
        t2 = (-Bq + dd) / (2 * Aq);

        // Testing ***************************
        Point temp = Rd * t1;
        Point ans1 = R0 + temp;

        temp = Rd * t2;
        Point ans2 = R0 + temp;

        if (ans2.z < 15 && ans1.z < 15)
            return min(t1, t2);
        else if (ans2.z < 15)
            return t2;
        else if (ans1.z < 15)
            return t1;
        else
            return -1;

        // Testing ***************************

        // if (t1 > 0)
        //     return t1;
        // else if (t2 > 0)
        //     return t2;
        // else
        //     return -1;

        //return min(t1, t2);
    }

    double intersect(Ray r, double *clr, int level)
    {
        double t = get_t(r);

        if (t < 1 || t > 1000)
            return -1;

        if (level == 0)
            return t;

        //  Adding Ambient light
        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];
    }
};

class Floor : public Object
{
public:
    int no_tiles;
    int floor_width;

    Floor() {}

    Floor(int floorWidth, int tileWidth)
    {
        reference_point = Point(-floorWidth / 2, -floorWidth / 2, 0);
        length = tileWidth;
        no_tiles = floorWidth / tileWidth;
        floor_width = floorWidth;
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

    void set_floor_color(Point p)
    {
        Point dist = p - reference_point;

        // if outside checker board then black
        if (dist.x < 0 || dist.x > floor_width || dist.y < 0 || dist.y > floor_width)
        {
            color[0] = color[1] = color[2] = 0.0;
            return;
        }

        int tile_x = (dist.x / length);
        int tile_y = (dist.y / length);

        // Determining white or black (1 or 0)
        color[0] = color[1] = color[2] = (tile_x + tile_y) % 2;
    }

    double get_t(Ray ray)
    {
        // checking if ray is parallel to floor (xy plane)
        if (ray.dir.z == 0)
            return -1;

        double t = (-ray.start.z / ray.dir.z);

        Point temp = ray.dir * t;
        Point intersection_point = ray.start + temp;

        set_floor_color(intersection_point);

        return t;
    }

    double intersect(Ray r, double *clr, int level)
    {
        double t = get_t(r);

        if (t < 1 || t > 1000)
            return -1;

        if (level == 0)
            return t;

        //  Adding Ambient light
        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];
    }
};