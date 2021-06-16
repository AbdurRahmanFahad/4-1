#include <bits/stdc++.h>

#include "bitmap_image.hpp"
#include "1605069_Header.h"
#include <windows.h>
#include <glut.h>

#define pi (2 * acos(0.0))

using namespace std;

int drawgrid = 1;
int drawaxes;

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

// Global Variables
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

void drawAxes()
{
    if (drawaxes == 1)
    {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_LINES);
        {
            glVertex3f(250, 0, 0);
            glVertex3f(-250, 0, 0);

            glVertex3f(0, -250, 0);
            glVertex3f(0, 250, 0);

            glVertex3f(0, 0, 250);
            glVertex3f(0, 0, -250);
        }
        glEnd();
    }
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);
    {
        glVertex3f(a, a, 2);
        glVertex3f(a, -a, 2);
        glVertex3f(-a, -a, 2);
        glVertex3f(-a, a, 2);
    }
    glEnd();
}

void drawCircle(double radius, int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7, 0.7, 0.7);
    //generate points
    for (i = 0; i <= segments; i++)
    {
        points[i].x = radius * cos(((double)i / (double)segments) * 2 * pi);
        points[i].y = radius * sin(((double)i / (double)segments) * 2 * pi);
    }
    //draw segments using generated points
    for (i = 0; i < segments; i++)
    {
        glBegin(GL_LINES);
        {
            glVertex3f(points[i].x, points[i].y, 0);
            glVertex3f(points[i + 1].x, points[i + 1].y, 0);
        }
        glEnd();
    }
}

void drawSphere(double radius, int slices, int stacks)
{
    struct point points[100][100];
    int i, j;
    double h, r;
    //generate points
    for (i = 0; i <= stacks; i++)
    {
        h = radius * sin(((double)i / (double)stacks) * (pi / 2));
        r = radius * cos(((double)i / (double)stacks) * (pi / 2));
        for (j = 0; j <= slices; j++)
        {
            points[i][j].x = r * cos(((double)j / (double)slices) * 2 * pi);
            points[i][j].y = r * sin(((double)j / (double)slices) * 2 * pi);
            points[i][j].z = h;
        }
    }
    //draw quads using generated points
    for (i = 0; i < stacks; i++)
    {
        glColor3f((double)i / (double)stacks, (double)i / (double)stacks, (double)i / (double)stacks);
        for (j = 0; j < slices; j++)
        {
            glBegin(GL_QUADS);
            {
                //upper hemisphere
                glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x, points[i][j].y, -points[i][j].z);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, -points[i][j + 1].z);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, -points[i + 1][j + 1].z);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, -points[i + 1][j].z);
            }
            glEnd();
        }
    }
}

void keyboardListener(unsigned char key, int x, int y)
{
    //print_my(l_gun);
    switch (key)
    {

    case 'g':
        drawgrid = 1 - drawgrid;
        break;
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

void mouseListener(int button, int state, int x, int y)
{ //x, y is the x-y of the screen (2D)
    switch (button)
    {
    case GLUT_LEFT_BUTTON:

        break;

    case GLUT_RIGHT_BUTTON:
        //........
        if (state == GLUT_DOWN)
        {
            drawaxes = 1 - drawaxes;
        }
        break;

    default:
        break;
    }
}

void draw_all()
{
    for (int i = 0; i < total_objects; i++)
    {
        objects[i]->draw();
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
    //gluLookAt(pos.x,pos.y,pos.z,	0,0,0,	0,0,1);
    glMatrixMode(GL_MODELVIEW);

    drawAxes();
    draw_all();

    glutSwapBuffers();
}

void animate()
{
    glutPostRedisplay();
}

void init()
{
    //codes for initialization
    drawgrid = 0;
    drawaxes = 1;

    glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

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

    // Floor ***********************

    temp = new Floor(1000, 20);
    // set color
    // set coEfficients
    // set shine
    objects.push_back(temp);
    total_objects++;
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
    //testing();

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
    glutMouseFunc(mouseListener);

    glutMainLoop(); //The main loop of OpenGL

    free_memory();
    return 0;
}