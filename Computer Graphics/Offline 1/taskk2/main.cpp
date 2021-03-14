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



struct point pos_bubble[5];
struct point vect_bubble[5];
float b1_speed = 3;
int is_inside[5] = {0};


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

		glColor3f(0, 0.7, 0);
		glBegin(GL_LINES);{
			glVertex3f( 500,0,0);
			glVertex3f(-500,0,0);

			glVertex3f(0,-500,0);
			glVertex3f(0, 500,0);
		}glEnd();
}

void drawSquare(double a)
{
    glColor3f(0,0.7,0);
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

    glColor3f(0,0,0.7);

    for(int i = 0; i<5; i++)
    {
        glPushMatrix();
        {
            glTranslatef(pos_bubble[i].x,pos_bubble[i].y,pos_bubble[i].z);
            drawCircle(30, 60);
            if(pos_bubble[i].y>500-30 || pos_bubble[i].y<30)
            {
                vect_bubble[i].y *= -1;
            }
            if(pos_bubble[i].x>500-30 || pos_bubble[i].x<30)
            {
                vect_bubble[i].x *= -1;
            }
        }
        glPopMatrix();
    }


    glColor3f(1,0,0);
    glTranslatef(250, 250, 0);
    drawCircle(150, 70);


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
        for(int i = 0; i<5; i++)
        {
            pos_bubble[i].x = pos_bubble[i].x + b1_speed*vect_bubble[i].x;
            pos_bubble[i].y = pos_bubble[i].y + b1_speed*vect_bubble[i].y;


            if( (pos_bubble[i].x-250)*(pos_bubble[i].x-250) +( pos_bubble[i].y-250)*(pos_bubble[i].y-250) < 120*120 )
            {
                is_inside[i] = 1;
            }

            vect_bubble[i] = normalize(vect_bubble[i]);

            if(is_inside[i])
            {
                double contact_x = pos_bubble[i].x + 30*vect_bubble[i].x;
                double contact_y = pos_bubble[i].y + 30*vect_bubble[i].y;

                if( (contact_x-250)*(contact_x-250) + (contact_y-250)*(contact_y-250) >= 150*150 )
                {
                    struct point normal = {250 - contact_x, 250 - contact_y, 0};
                    normal = normalize(normal);
                    double dot_value = normal.x*vect_bubble[i].x + normal.y*vect_bubble[i].y;
                    dot_value *= 2;
                    normal.x *= dot_value;
                    normal.y *= dot_value;
                    vect_bubble[i].x -= normal.x;
                    vect_bubble[i].y -= normal.y;
                }



            }


        }
    }



	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
    for(int i = 0; i<5; i++)
    {
        pos_bubble[i] = {30,30,0};
    }
    vect_bubble[0] = {.3578, .82, 0};
    vect_bubble[1] = {.3578, -.24, 0};
    vect_bubble[2] = {.49, .22, 0};
    vect_bubble[3] = {.3578, .55, 0};
    vect_bubble[4] = {.3578, .39, 0};


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















