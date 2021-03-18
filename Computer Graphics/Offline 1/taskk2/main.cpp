#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include <windows.h>
#include <glut.h>
#include <iostream>

#define pi (2*acos(0.0))

using namespace std;

struct point
{
	double x,y,z;
};

int N = 1;
int timez = 0;
struct point pos_bubble[5];
struct point vect_bubble[5];
float b1_speed = 1;
int is_inside[5] = {0};

int is_paused = 1;

struct point normalize(struct point v)
{
    struct point res = {0,0,0};
    double modulas = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
    res.x = v.x/modulas;
    res.y = v.y/modulas;
    res.z = v.z/modulas;

    return res;
};


struct point get_reflection(struct point v1, struct point v2)
{
    struct point res = {0,0,0};

    v2 = normalize(v2);

    double dot = v1.x*v2.x + v1.y*v2.y;

    res.x = v1.x - 2*dot*v2.x;
    res.y = v1.y - 2*dot*v2.y;


    return normalize(res);
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



    if(!is_paused)
    {

        for(int i = 0; i<N; i++){

            if( (pos_bubble[i].x-250)*(pos_bubble[i].x-250) +( pos_bubble[i].y-250)*(pos_bubble[i].y-250) < 129*130 )
                is_inside[i] = 1;

            vect_bubble[i] = normalize(vect_bubble[i]);

            if(is_inside[i])
            {
                double contact_x = pos_bubble[i].x + 20*vect_bubble[i].x;
                double contact_y = pos_bubble[i].y + 20*vect_bubble[i].y;
                //double check1 = (contact_x-250)*(contact_x-250) + (contact_y-250)*(contact_y-250);
                double check2 = (pos_bubble[i].x-250)*(pos_bubble[i].x-250) + (pos_bubble[i].y-250)*(pos_bubble[i].y-250);

                //check1 >= 149*149  ||
                if(  check2 >= 129*130)
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




        for(int p = 0; p<N; p++)
            {
                for(int q = p+1; q<N; q++)
                {
                    if(is_inside[p]!=1 || is_inside[q]!=1)
                        continue;

                    double xx = pos_bubble[p].x-pos_bubble[q].x;
                    double yy = pos_bubble[p].y-pos_bubble[q].y;

                    if( xx*xx + yy*yy < 40.1*40)
                    {
                        struct point temp = { -xx,-yy, 0};
                        struct point temp3 = { xx,yy, 0};

                        struct point temp1 = get_reflection(vect_bubble[p], temp);
                        struct point temp2 = get_reflection(vect_bubble[q], temp3);

                        vect_bubble[p].x = temp1.x;
                        vect_bubble[p].y = temp1.y;

                        //if(vect_bubble[p].x*vect_bubble[q].x + vect_bubble[p].y*vect_bubble[q].y >0)

                        vect_bubble[q].x = temp2.x;
                        vect_bubble[q].y = temp2.y;
                    }
                }

            }

    }









    glRotatef(-90, 0,0,1);
    glColor3f(1,0,0);

    drawSquare(250);

    glColor3f(0,0,0.7);

    for(int i = 0; i<N; i++)
    {
        glPushMatrix();
        {
            glTranslatef(pos_bubble[i].x,pos_bubble[i].y,pos_bubble[i].z);
            drawCircle(20, 40);
            if(pos_bubble[i].y>500-20 || pos_bubble[i].y<20)
            {
                vect_bubble[i].y *= -1;
            }
            if(pos_bubble[i].x>500-20 || pos_bubble[i].x<20)
            {
                vect_bubble[i].x *= -1;
            }

        }
        glPopMatrix();
    }


    glColor3f(1,0,0);
    glTranslatef(250, 250, 0);
    drawCircle(150, 70);

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

		case GLUT_KEY_DOWN:
		    if(b1_speed>.5)		//down arrow key
            b1_speed -= .1;
			break;
		case GLUT_KEY_UP:		// up arrow key
            if(b1_speed<3)		//down arrow key
            b1_speed += .1;
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:

			break;

		default:
			break;
	}
}


void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(250,-250,360,	250,-250,0,	1,0,0);
    glMatrixMode(GL_MODELVIEW);

	drawAxes();

     drawSS();

 	glutSwapBuffers();
}


void animate(){
	if(!is_paused)
    {
        for(int i = 0; i<N; i++)
        {
            pos_bubble[i].x = pos_bubble[i].x + b1_speed*vect_bubble[i].x;
            pos_bubble[i].y = pos_bubble[i].y + b1_speed*vect_bubble[i].y;




            if(N<5)
                timez++;
            if(timez%300==0 && N<5)
            {
                N++;
                //cout<<timez<<" "<<N<<endl;
            }

        }







    }

	glutPostRedisplay();
}

void init(){

    for(int i = 0; i<5; i++)
        pos_bubble[i] = {30,30,0};

    srand(time(0));

    for(int i = 0; i<5; i++)
    {
        double f1 = (double)rand() / RAND_MAX;
        double f2 = (double)rand() / RAND_MAX;
        cout<<f1<<" "<<f2<<endl;
        vect_bubble[i] = {f1,f2,0};
        vect_bubble[i] = normalize(vect_bubble[i]);

    }

	glClearColor(0,0,0,0);


	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

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















