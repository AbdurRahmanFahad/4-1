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

    Point(double a, double b, double c)
    {
        x = a, y = b, z = c;
    }

    Point operator+(Point p)
    {
        return Point(x + p.x, y + p.y, z + p.z);
    }

    Point operator-(Point p)
    {
        return Point(x - p.x, y - p.y, z - p.z);
    }

    Point operator*(double d)
    {
        return Point(x * d, y * d, z * d);
    }

    void Normalize()
    {
        double modulas = sqrt(x * x + y * y + z * z);

        if (modulas != 0)
            x = x / modulas, y = y / modulas, z = z / modulas;
    }

    friend ostream &operator<<(ostream &os, Point p)
    {
        os << p.x << " " << p.y << " " << p.z << endl;
        return os;
    }
};

double Dot_product(Point a, Point b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point Cross_product(Point a, Point b)
{
    Point res;

    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;

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

Point get_intersection_point(Ray ray, double t)
{
    // P(t) = R0 + t*Rd
    Point Rd = ray.dir, R0 = ray.start;

    Point ans = R0 + Rd * t;

    return ans;
}

Point get_reflected_vector(Point incident_ray, Point normal)
{
    // r = d − 2(d⋅n)n, d is incident ray, n is normal

    double k = 2 * Dot_product(incident_ray, normal);
    Point reflected = incident_ray - normal * k;
    reflected.Normalize();

    return reflected;
}

Point get_reverse_reflection(Point incident_ray, Point normal)
{
    double k = 2 * Dot_product(incident_ray, normal);
    Point reflected = normal * k - incident_ray; // r = 2(d⋅n)n - d
    reflected.Normalize();

    return reflected;
}

class Object
{
public:
    Point reference_point;
    double height, width, length;
    double color[3];
    double coEfficients[4]; // reflection coefficients
    int shine;
    int object_id;

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

    virtual double get_t(Ray r)
    {
        return -1;
    }

    virtual double intersect(Ray r, double *color, int level)
    {
        return -1.0;
    }
};

extern vector<Object *> objects;
extern vector<Light> lights;
extern int recursion_level;

void Illuminati(Point intersection_point, Point normal, Ray r, int id, double *clr)
{
    // Illumination ***********************************

    // Adding Diffuse, Specular lightings

    for (int i = 0; i < lights.size(); i++)
    {
        Point L = lights[i].light_pos - intersection_point;
        L.Normalize();

        Point start = intersection_point + L;
        Ray sunLight(start, L);

        Point N = normal;
        Point R = get_reverse_reflection(L, N);

        Point V = r.start - intersection_point;
        V.Normalize();

        //check if obscured
        bool obscured = false;
        for (int j = 0; j < objects.size(); j++)
        {
            double temp = objects[j]->get_t(sunLight);

            if (temp > 0)
            {
                obscured = true;
                break;
            }
        }

        if (!obscured)
        {
            double cosTheta = max(0.0, Dot_product(L, N));
            double cosPhi = max(0.0, Dot_product(R, V));

            double lambart = objects[id]->coEfficients[1] * cosTheta;
            double phong = pow(cosPhi, objects[id]->shine);

            // calculate phongValue using r, rayr
            // color += l.color * coEfficient[DIFF] *lambertValue *intersectionPointColor
            // color += l.color * coEfficient[SPEC] * phongValue^shine * intersectionPointColor
            for (int c = 0; c < 3; c++)
                clr[c] += (lambart + phong) * lights[i].color[c] * objects[id]->color[c];
        }
    }
}

void reflectionati(Point intersection_point, Point reflected_vector, int level, int id, double *clr)
{
    int nearest, t_min, t2;

    // Adding Reflection lighting

    if (level < recursion_level)
    {
        Point start = intersection_point + reflected_vector;
        Ray reflected_ray(start, reflected_vector);

        nearest = -1;
        t_min = 10000;

        double *reflected_color = new double[3];
        reflected_color[0] = reflected_color[1] = reflected_color[2] = 0.0;

        for (int k = 0; k < objects.size(); k++)
        {
            t2 = objects[k]->intersect(reflected_ray, reflected_color, 0);

            if (t2 > 0 && t2 < t_min)
                t_min = t2, nearest = k;
        }

        if (nearest != -1)
        {
            t2 = objects[nearest]->intersect(reflected_ray, reflected_color, level + 1);

            for (int c = 0; c < 3; c++)
                clr[c] += (reflected_color[c] * objects[id]->coEfficients[3]);
        }

        delete[] reflected_color;
    }
}

class Sphere : public Object
{
public:
    Sphere() {}

    Sphere(Point center, double radius)
    {
        reference_point = center;
        length = radius;
    }

    Point getNormal(Point x, Point y)
    {
        Point temp = x - y;

        temp.Normalize();

        return temp;
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

        if (t < 1 || t > 10000)
            return -1;

        if (level == 0)
            return t;

        Point intersection_point = get_intersection_point(r, t);
        Point normal = getNormal(intersection_point, reference_point);
        Point reflected_vector = get_reflected_vector(r.dir, normal);

        // Illumination ***********************************

        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];

        Illuminati(intersection_point, normal, r, object_id, clr);

        // Illumination ***********************************

        //Reflection **************************************

        reflectionati(intersection_point, reflected_vector, level, object_id, clr);

        //Reflection **************************************

        return t;
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

    Point getNormal()
    {
        // (b - a) x (c - a);
        Point temp = Cross_product(p2 - p1, p3 - p1);

        temp.Normalize();

        return temp;
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

        if (t < 1 || t > 10000)
            return -1;

        if (level == 0)
            return t;

        Point intersection_point = get_intersection_point(r, t);
        Point normal = getNormal();
        Point reflected_vector = get_reflected_vector(r.dir, normal);

        // Illumination ***********************************

        //  Adding Ambient light
        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];

        Illuminati(intersection_point, normal, r, object_id, clr);

        // Illumination ***********************************

        //Reflection **************************************

        reflectionati(intersection_point, reflected_vector, level, object_id, clr);

        //Reflection **************************************

        return t;
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

    Point getNormal(Point p)
    {

        //Normal = (𝜕F/𝜕x, 𝜕F/𝜕y, 𝜕F/𝜕z)
        //[Substitute x, y, z values with that of intersection
        //point to obtain normals at different points]
        double xx = 2 * A * p.x + D * p.y + G;
        double yy = 2 * B * p.y + F * p.z + H;
        double zz = 2 * C * p.z + E * p.x + I;

        Point temp(xx, yy, zz);
        temp.Normalize();

        return temp;
    }

    void draw()
    {
        //cout << "Drawing General" << endl;
    }

    double get_t(Ray ray)
    {
        double Aq, Bq, Cq;
        Point R0 = ray.start, Rd = ray.dir;

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

        Point ans1 = R0 + Rd * t1;
        Point ans2 = R0 + Rd * t2;

        // Testing ***************************

        bool check_x1 = length > 0 && (ans1.x > reference_point.x + length || ans1.x < reference_point.x);
        bool check_y1 = width > 0 && (ans1.y > reference_point.y + width || ans1.y < reference_point.y);
        bool check_z1 = height > 0 && (ans1.z > reference_point.z + height || ans1.z < reference_point.z);

        bool check_x2 = length > 0 && (ans2.x > reference_point.x + length || ans2.x < reference_point.x);
        bool check_y2 = width > 0 && (ans2.y > reference_point.y + width || ans2.y < reference_point.y);
        bool check_z2 = height > 0 && (ans2.z > reference_point.z + height || ans2.z < reference_point.z);

        bool check_1 = check_x1 || check_y1 || check_z1;
        bool check_2 = check_x2 || check_y2 || check_z2;

        if (check_1 && check_2) // both point outside bound
            return -1;
        else if (check_1) // Point 1 outside bound, return point 2
            return t2;
        else if (check_2)
            return t1;
        else
            return min(t1, t2);
    }

    double intersect(Ray r, double *clr, int level)
    {
        double t = get_t(r);

        if (t < 1 || t > 10000)
            return -1;

        if (level == 0)
            return t;

        Point intersection_point = get_intersection_point(r, t);
        Point normal = getNormal(intersection_point);
        Point reflected_vector = get_reflected_vector(r.dir, normal);

        // Illumination ***********************************

        //  Adding Ambient light
        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];

        Illuminati(intersection_point, normal, r, object_id, clr);

        // Illumination ***********************************

        //Reflection **************************************

        reflectionati(intersection_point, reflected_vector, level, object_id, clr);

        //Reflection **************************************

        return t;
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
        coEfficients[0] = 0.4;
        coEfficients[1] = 0.4;
        coEfficients[2] = 0.4;
        coEfficients[3] = 0.4;
        shine = 5;
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

        if (t < 1 || t > 10000)
            return -1;

        if (level == 0)
            return t;

        Point intersection_point = get_intersection_point(r, t);
        Point normal(0, 0, 1);
        Point reflected_vector = get_reflected_vector(r.dir, normal);

        // Illumination ***********************************

        //  Adding Ambient light
        for (int i = 0; i < 3; i++)
            clr[i] = color[i] * coEfficients[0];

        Illuminati(intersection_point, normal, r, object_id, clr);

        // Illumination ***********************************

        //Reflection **************************************

        reflectionati(intersection_point, reflected_vector, level, object_id, clr);

        //Reflection **************************************

        return t;
    }
};
