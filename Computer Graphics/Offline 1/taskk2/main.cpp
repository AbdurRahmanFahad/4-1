#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>
#include <iostream>

#define pi (2*acos(0.0))

using namespace std;

struct point
{
	double x,y,z;
};

struct point u = {0,0,1};
struct point b1_pos = {30, 30, 0};
struct point b1_vect = {.3578, 1, 0};
float b1_speed = 3, b1_trans = 0;

struct point b2_pos = {370, 30, 0};
struct point b2_vect = {.3578, -.24, 0};
float b2_speed = 3, b2_trans = 0;

struct point b3_pos = {30, 370, 0};
struct point b3_vect = {.3578, 1, 0};
float b3_speed = 3, b3_trans = 0;

struct point b4_pos = {80, 200, 0};
struct point b4_vect = {.3578, .55, 0};
float b4_speed = 3, b4_trans = 0;

struct point b5_pos = {330, 110, 0};
struct point b5_vect = {.3578, .39, 0};
float b5_speed = 3, b5_trans = 0;


int is_paused = 1;



void print_my(struct point u_gun)
{
    cout<<u_gun.x<<" "<<u_gun.y<<" "<<u_gun.z<<endl;
}

void print_my2(struct point u_gun)
{
    cout<<u_gun.x<<" "<<u_gun.y<<" "<<u_gun.z<<" ";
}

struct point cross_product(struct point v1, struct point v2)
{
    struct point res = {0,0,0};

    res.x = v1.y*v2.z - v1.z*v2.y;
    res.y = v1.z*v2.x - v1.x*v2.z;
    res.z = v1.x*v2.y - v1.y*v2.x;

    return res;
};

struct point normalize(struct point v)
{
    struct point res = {0,0,0};
    double modulas = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    res.x = v.x/modulas;
    res.y = v.y/modulas;
    res.z = v.z/modulas;

    return res;
};

void drawAxes()
{

		glColor3f(1.0, 0, 0);
		glBegin(GL_LINES);{
			glVertex3f( 500,0,0);
			glVertex3f(-500,0,0);

			glVertex3f(0,-500,0);
			glVertex3f(0, 500,0);
		}glEnd();
}

void drawSquare(double a)
{
    glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINES);{
			glVertex3f( 2*a,2*a,0);
			glVertex3f( 0,2*a,0);

			glVertex3f( 2*a,2*a,0);
			glVertex3f( 2*a,0, 0);

		}glEnd();
}

void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0,0.7,0);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawSS()
{
    glRotatef(-90, 0,0,1);
    glColor3f(1,0,0);

    drawSquare(250);

    //glTranslatef(30,30,0);

    //glTranslatef(b1_vect.x*b1_trans, b1_vect.y*b1_trans, 0);
    glPushMatrix();
    {
        glTranslatef(b1_pos.x,b1_pos.y,b1_pos.z);
        drawCircle(30, 60);
        if(b1_pos.y>500-30 || b1_pos.y<30)
        {
            b1_vect.y *= -1;
        }
        if(b1_pos.x>500-30 || b1_pos.x<30)
        {
            b1_vect.x *= -1;
        }
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(b2_pos.x,b2_pos.y,b2_pos.z);
        drawCircle(30, 60);
        if(b2_pos.y>500-30 || b2_pos.y<30)
        {
            b2_vect.y *= -1;
        }
        if(b2_pos.x>500-30 || b2_pos.x<30)
        {
            b2_vect.x *= -1;
        }
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(b3_pos.x,b3_pos.y,b3_pos.z);
        drawCircle(30, 60);
        if(b3_pos.y>500-30 || b3_pos.y<30)
        {
            b3_vect.y *= -1;
        }
        if(b3_pos.x>500-30 || b3_pos.x<30)
        {
            b3_vect.x *= -1;
        }
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(b4_pos.x,b4_pos.y,b4_pos.z);
        drawCircle(30, 60);
        if(b4_pos.y>500-30 || b4_pos.y<30)
        {
            b4_vect.y *= -1;
        }
        if(b4_pos.x>500-30 || b4_pos.x<30)
        {
            b4_vect.x *= -1;
        }
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(b5_pos.x,b5_pos.y,b5_pos.z);
        drawCircle(30, 60);
        if(b5_pos.y>500-30 || b5_pos.y<30)
        {
            b5_vect.y *= -1;
        }
        if(b5_pos.x>500-30 || b5_pos.x<30)
        {
            b5_vect.x *= -1;
        }
    }
    glPopMatrix();



    /*{


    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);

    glPushMatrix();
    {
        glRotatef(angle,0,0,1);
        glTranslatef(60,0,0);
        glRotatef(2*angle,0,0,1);
        glColor3f(0,0,1);
        drawSquare(10);
    }
    glPopMatrix();

    glRotatef(3*angle,0,0,1);
    glTranslatef(40,0,0);
    glRotatef(4*angle,0,0,1);
    glColor3f(1,1,0);
    drawSquare(5);

    */

}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

    case 'p':
        is_paused = 1 - is_paused;
        cout<<"Paused"<<endl;
        break;

    default:
        break;


	}

}


void specialKeyListener(int key, int x,int y){
	switch(key){

		case GLUT_KEY_DOWN:		//down arrow key

			break;
		case GLUT_KEY_UP:		// up arrow key

			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:

			break;

		case GLUT_RIGHT_BUTTON:
			//........

			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}


void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	//gluLookAt(100,100,100,	0,0,0,	0,0,1);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	gluLookAt(250,-250,360,	250,-250,0,	1,0,0);
    //gluLookAt(pos.x,pos.y,pos.z,	0,0,0,	u.x,u.y,u.z);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();

    //glColor3f(1,0,0);
    //drawSquare(10);

    drawSS();

    //drawCircle(30,24);

    //drawCone(20,50,24);

	//drawSphere(30,24,20);




	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//angle+=0.05;
	if(!is_paused)
    {
        b1_trans += b1_speed;
        b1_pos.x = b1_pos.x + b1_speed*b1_vect.x;
        b1_pos.y = b1_pos.y + b1_speed*b1_vect.y;
        b1_pos.z = b1_pos.z + b1_speed*b1_vect.z;

        print_my2(b1_pos);
        print_my2(b2_pos);
        print_my2(b3_pos);
        print_my2(b4_pos);
        print_my2(b5_pos);
        cout<<endl;

        b2_trans += b2_speed;
        b2_pos.x = b2_pos.x + b2_speed*b2_vect.x;
        b2_pos.y = b2_pos.y + b2_speed*b2_vect.y;
        b2_pos.z = b2_pos.z + b2_speed*b2_vect.z;

        b3_trans += b3_speed;
        b3_pos.x = b3_pos.x + b3_speed*b3_vect.x;
        b3_pos.y = b3_pos.y + b3_speed*b3_vect.y;
        b3_pos.z = b3_pos.z + b3_speed*b3_vect.z;


        b4_trans += b4_speed;
        b4_pos.x = b4_pos.x + b4_speed*b4_vect.x;
        b4_pos.y = b4_pos.y + b4_speed*b4_vect.y;
        b4_pos.z = b4_pos.z + b4_speed*b4_vect.z;

        b5_trans += b5_speed;
        b5_pos.x = b5_pos.x + b5_speed*b5_vect.x;
        b5_pos.y = b5_pos.y + b5_speed*b5_vect.y;
        b5_pos.z = b5_pos.z + b5_speed*b5_vect.z;

    }
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My Program 2");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}















