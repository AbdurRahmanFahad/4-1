#include <bits/stdc++.h>

#include "bitmap_image.hpp"
#include "1605069_Header.h"
#include <windows.h>
#include <glut.h>

#define pi (2 * acos(0.0))

using namespace std;

struct point
{
    double x, y, z;
};

// Variables for camera

struct point pos = {100, 100, 60};
struct point u = {0, 0, 1};
struct point r = {-1 / sqrt(2), 1 / sqrt(2), 0};
struct point l = {-1 / sqrt(2), -1 / sqrt(2), 0};

// Vectors for objects and light sources

vector<Object *> objects;
vector<Light> lights;

// Global Variables ***********************************

int recursion_level, pixels, total_objects, total_light_sources;

struct point cross_product(struct point v1, struct point v2)
{
    struct point res = {0, 0, 0};

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;

    return res;
};

struct point normalize(struct point v)
{
    struct point res = {0, 0, 0};
    double modulas = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    res.x = v.x / modulas;
    res.y = v.y / modulas;
    res.z = v.z / modulas;

    return res;
};

// Capture Function ***********************************

void Capture()
{
    // View angle is 80, windowHeight is 500
    double theta = (80.0 / 2.0);
    theta = (pi * theta) / 180.0;
    double planeDistance = (500 / 2) / tan(theta);

    Point uu(u.x, u.y, u.z);
    Point rr(r.x, r.y, r.z);
    Point ll(l.x, l.y, l.z);
    Point eye(pos.x, pos.y, pos.z);

    // topleft = eye + l*planeDistance - r*windowWidth/2 + u*windowHeight / 2
    Point topleft = eye + ll * planeDistance - rr * 250.0 + uu * 250.0;

    double du = (double)500 / pixels; // window_Width = 500
    double dv = (double)500 / pixels; // window_Height = 500

    //// Choose middle of the grid cell
    //topleft = topleft + r * (0.5 * du) - u * (0.5 * dv)

    int nearest;
    double t, tMin;
    Point curPixel;
    double dummyColor[3];

    bitmap_image image(pixels, pixels);

    for (int i = 0; i < pixels; i++)
    {
        for (int j = 0; j < pixels; j++)
        {
            curPixel = topleft + rr * (i * du) - uu * (j * dv);

            Ray cast_ray(eye, curPixel - eye);

            nearest = -1;
            tMin = 10000;

            // Knowing which is the nearest object
            for (int k = 0; k < objects.size(); k++)
            {
                //level 0  to know the nearest object
                t = objects[k]->intersect(cast_ray, dummyColor, 0);

                if (t > 0 && t < tMin)
                    tMin = t, nearest = k;
            }

            if (nearest != -1)
            {
                t = objects[nearest]->intersect(cast_ray, dummyColor, 1);

                for (int pp = 0; pp < 3; pp++)
                {
                    // keeping values between 0 and 1
                    if (dummyColor[pp] < 0.0)
                        dummyColor[pp] = 0.0;

                    else if (dummyColor[pp] > 1.0)
                        dummyColor[pp] = 1.0;
                }
            }
            else // black screen, no object, no floor
            {
                dummyColor[0] = 0.0;
                dummyColor[1] = 0.0;
                dummyColor[2] = 0.0;
            }

            image.set_pixel(i, j, 255 * dummyColor[0], 255 * dummyColor[1], 255 * dummyColor[2]);
        }
    }

    image.save_image("image.bmp");
    image.clear();

    cout << "Capture()" << endl;
}

// Capture Function ***********************************

void keyboardListener(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
    {
        l.x = l.x * cos(2 * pi - 3 * pi / 180.0) + r.x * sin(2 * pi - 3 * pi / 180.0);
        l.y = l.y * cos(2 * pi - 3 * pi / 180.0) + r.y * sin(2 * pi - 3 * pi / 180.0);
        l.z = l.z * cos(2 * pi - 3 * pi / 180.0) + r.z * sin(2 * pi - 3 * pi / 180.0);
        l = normalize(l);
        r = cross_product(l, u);
        r = normalize(r);
    }
    break;
    case '2':
    {
        l.x = l.x * cos(3 * pi / 180.0) + r.x * sin(3 * pi / 180.0);
        l.y = l.y * cos(3 * pi / 180.0) + r.y * sin(3 * pi / 180.0);
        l.z = l.z * cos(3 * pi / 180.0) + r.z * sin(3 * pi / 180.0);
        l = normalize(l);
        r = cross_product(l, u);
        r = normalize(r);
    }
    break;
    case '3':
    {
        l.x = l.x * cos(3 * pi / 180.0) + u.x * sin(3 * pi / 180.0);
        l.y = l.y * cos(3 * pi / 180.0) + u.y * sin(3 * pi / 180.0);
        l.z = l.z * cos(3 * pi / 180.0) + u.z * sin(3 * pi / 180.0);
        l = normalize(l);
        u = cross_product(r, l);
        u = normalize(u);
    }
    break;
    case '4':
    {
        l.x = l.x * cos(2 * pi - 3 * pi / 180.0) + u.x * sin(2 * pi - 3 * pi / 180.0);
        l.y = l.y * cos(2 * pi - 3 * pi / 180.0) + u.y * sin(2 * pi - 3 * pi / 180.0);
        l.z = l.z * cos(2 * pi - 3 * pi / 180.0) + u.z * sin(2 * pi - 3 * pi / 180.0);
        l = normalize(l);
        u = cross_product(r, l);
        u = normalize(u);
    }
    break;
    case '5':
    {
        u.x = u.x * cos(2 * pi - 3 * pi / 180.0) + r.x * sin(2 * pi - 3 * pi / 180.0);
        u.y = u.y * cos(2 * pi - 3 * pi / 180.0) + r.y * sin(2 * pi - 3 * pi / 180.0);
        u.z = u.z * cos(2 * pi - 3 * pi / 180.0) + r.z * sin(2 * pi - 3 * pi / 180.0);
        u = normalize(u);
        r = cross_product(l, u);
        r = normalize(r);
    }
    break;
    case '6':
    {
        u.x = u.x * cos(3 * pi / 180.0) + r.x * sin(3 * pi / 180.0);
        u.y = u.y * cos(3 * pi / 180.0) + r.y * sin(3 * pi / 180.0);
        u.z = u.z * cos(3 * pi / 180.0) + r.z * sin(3 * pi / 180.0);
        u = normalize(u);
        r = cross_product(l, u);
        r = normalize(r);
    }
    break;
    case '0':
        Capture();
        break;
    default:
        break;
    }
}

void specialKeyListener(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_DOWN: //down arrow key
        pos.x -= 2 * l.x;
        pos.y -= 2 * l.y;
        pos.z -= 2 * l.z;
        break;
    case GLUT_KEY_UP: // up arrow key
        pos.x += 2 * l.x;
        pos.y += 2 * l.y;
        pos.z += 2 * l.z;
        break;

    case GLUT_KEY_RIGHT:
        pos.x += 2 * r.x;
        pos.y += 2 * r.y;
        pos.z += 2 * r.z;
        break;
    case GLUT_KEY_LEFT:
        pos.x -= 2 * r.x;
        pos.y -= 2 * r.y;
        pos.z -= 2 * r.z;
        break;

    case GLUT_KEY_PAGE_UP:
        pos.x += 2 * u.x;
        pos.y += 2 * u.y;
        pos.z += 2 * u.z;
        break;
    case GLUT_KEY_PAGE_DOWN:
        pos.x -= 2 * u.x;
        pos.y -= 2 * u.y;
        pos.z -= 2 * u.z;
        break;

    default:
        break;
    }
}

void draw_all()
{
    // Drawing Objects
    for (int i = 0; i < total_objects; i++)
    {
        objects[i]->draw();
    }

    // Drawing Light Sources
    for (int i = 0; i < total_light_sources; i++)
    {
        lights[i].draw();
    }
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0); //color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    gluLookAt(pos.x, pos.y, pos.z, pos.x + l.x, pos.y + l.y, pos.z + l.z, u.x, u.y, u.z);

    glMatrixMode(GL_MODELVIEW);

    draw_all();

    glutSwapBuffers();
}

void animate()
{
    glutPostRedisplay();
}

void init()
{

    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    // Fov - Field of View 80 degrees
    gluPerspective(80, 1, 1, 1000.0);
}

// ****************** Offline 3 codes here ******************

void loadData()
{
    freopen("scene.txt", "r", stdin);
    cin >> recursion_level;
    cin >> pixels;
    cin >> total_objects;

    Object *temp;

    for (int i = 0; i < total_objects; i++)
    {
        string s;
        cin >> s;
        if (s == "sphere")
        {
            // Input
            double x, y, z, radius, r, g, b;
            double ambient, diffuse, specular, recursive_reflection_coefficient;
            int shininess;
            cin >> x >> y >> z;
            cin >> radius;
            cin >> r >> g >> b;
            cin >> ambient >> diffuse >> specular >> recursive_reflection_coefficient;
            cin >> shininess;

            // make object

            temp = new Sphere(Point(x, y, z), radius);
            temp->setColor(r, g, b);
            temp->setShine(shininess);
            temp->setCoEfficients(ambient, diffuse, specular, recursive_reflection_coefficient);
            temp->object_id = i;
            objects.push_back(temp);
        }
        else if (s == "triangle")
        {
            // Input

            double x1, y1, z1, x2, y2, z2, x3, y3, z3;
            double r, g, b;
            double ambient, diffuse, specular, recursive_reflection_coefficient;
            int shininess;

            cin >> x1 >> y1 >> z1;
            cin >> x2 >> y2 >> z2;
            cin >> x3 >> y3 >> z3;

            cin >> r >> g >> b;

            cin >> ambient >> diffuse >> specular >> recursive_reflection_coefficient;
            cin >> shininess;

            // make object

            temp = new Triangle(Point(x1, y1, z1), Point(x2, y2, z2), Point(x3, y3, z3));
            temp->setColor(r, g, b);
            temp->setShine(shininess);
            temp->setCoEfficients(ambient, diffuse, specular, recursive_reflection_coefficient);
            temp->object_id = i;
            objects.push_back(temp);
        }
        else if (s == "general")
        {
            // Input
            double A, B, C, D, E, F, G, H, I, J;
            cin >> A >> B >> C >> D >> E >> F >> G >> H >> I >> J;
            double x, y, z, length, width, height;
            cin >> x >> y >> z >> length >> width >> height;

            double r, g, b;
            double ambient, diffuse, specular, recursive_reflection_coefficient;
            int shininess;
            cin >> r >> g >> b;
            cin >> ambient >> diffuse >> specular >> recursive_reflection_coefficient;
            cin >> shininess;

            // make object
            General *temp1;
            temp1 = new General(Point(x, y, z), length, width, height);
            temp1->set_ABCD(A, B, C, D, E, F, G, H, I, J);
            temp1->setColor(r, g, b);
            temp1->setShine(shininess);
            temp1->setCoEfficients(ambient, diffuse, specular, recursive_reflection_coefficient);
            temp->object_id = i;
            objects.push_back(temp1);
        }
    }

    // Light Sources Input ********

    cin >> total_light_sources;
    for (int i = 0; i < total_light_sources; i++)
    {
        double x, y, z;
        cin >> x >> y >> z;
        double r, g, b;
        cin >> r >> g >> b;
        Light l(Point(x, y, z), r, g, b);
        lights.push_back(l);
    }

    // Light Sources Input ********

    // Floor ***********************

    temp = new Floor(500, 20);
    temp->object_id = total_objects;
    objects.push_back(temp);
    total_objects++;

    // Floor ***********************
}

void free_memory()
{
    for (int i = 0; i < total_objects; i++)
    {
        Object *p = objects.back();
        objects.pop_back();
        delete p;
    }

    lights.clear();
}

// ****************** Offline 3 codes end here ******************

int main(int argc, char **argv)
{

    loadData();

    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB); //Depth, Double buffer, RGB color

    glutCreateWindow("Oflline 3 Ray Tracing");

    init();

    glEnable(GL_DEPTH_TEST); //enable Depth Testing

    glutDisplayFunc(display); //display callback function
    glutIdleFunc(animate);    //what you want to do in the idle time (when no drawing is occurring)

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutMainLoop(); //The main loop of OpenGL

    free_memory();
    return 0;
}
