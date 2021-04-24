#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>
#include <iostream>

#define pi (2*acos(0.0))

using namespace std;

int drawgrid;
int drawaxes;
double angle;
double theta_xy;
double theta_yz;
double theta_xz;
double theta_gun = 0;
int gunshots = 0;

double shots[100][2];

struct point
{
	double x,y,z;
};

struct point pos = {100,100,60};
//struct point pos = {250,0,0};
struct point u = {0,0,1};
struct point r = {-1/sqrt(2),1/sqrt(2),0};
struct point l = {-1/sqrt(2),-1/sqrt(2),0};
//struct point l = {-1,0,0};

struct point l_gun = {0,1,0};
struct point u_gun = {0,0,1};
struct point r_gun = {1,0,0};

struct point gun_point = {0,30,0};

void print_my(struct point u_gun)
{
    cout<<u_gun.x<<" "<<u_gun.y<<" "<<u_gun.z<<endl;
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
	if(drawaxes==1)
	{
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 250,0,0);
			glVertex3f(-250,0,0);

			glVertex3f(0,-250,0);
			glVertex3f(0, 250,0);

			glVertex3f(0,0, 250);
			glVertex3f(0,0,-250);
		}glEnd();
	}
}


void drawGrid()
{
	int i;
	if(drawgrid==1)
	{
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}

void drawPlane()
{
    double a = 112;
    glColor3f(0.7,0.7,0.7);
	glBegin(GL_QUADS);{
		glVertex3f( a, 250,a);
		glVertex3f( a,250,-a);
		glVertex3f(-a,250,-a);
		glVertex3f(-a, 250,a);
	}glEnd();
}


void draw_half_circle()
{

    struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	double radius = 11;
	int stacks = 89, slices = 89;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));

		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].z=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].y=11-h;
		}
	}


	//draw quads using generated points
	int flag = 1;
	for(i=0;i<stacks;i++)
	{
        flag = 1;
		for(j=0;j<slices;j++)
		{
		    if(j%2==0)
            {
                if(flag)
                {
                    glColor3f(0,0,0);
                    flag = 0;
                }
                else
                {
                    glColor3f(0.9,0.9,0.9);
                    flag = 1;

                }
            }


			glBegin(GL_QUADS);{
			    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}
	}



}

void boro_half_circle1()
{

    struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	double radius = 30;
	int stacks = 89, slices = 89;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));

		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].z=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].y=h-30;
		}
	}


	//draw quads using generated points
	int flag = 1;
	for(i=0;i<stacks;i++)
	{
        flag = 1;
		for(j=0;j<slices;j++)
		{
		    if(j%2==0)
            {
                if(flag)
                {
                    glColor3f(0,0,0);
                    flag = 0;
                }
                else
                {
                    glColor3f(0.9,0.9,0.9);
                    flag = 1;

                }
            }


			glBegin(GL_QUADS);{
			    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}
	}



}

void boro_half_circle2()
{

    struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	double radius = 30;
	int stacks = 89, slices = 89;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));

		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].z=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].y=-30-h;
		}
	}


	//draw quads using generated points
	int flag = 1;
	for(i=0;i<stacks;i++)
	{
        flag = 1;
		for(j=0;j<slices;j++)
		{
		    if(j%2==0)
            {
                if(flag)
                {
                    glColor3f(0,0,0);
                    flag = 0;
                }
                else
                {
                    glColor3f(0.9,0.9,0.9);
                    flag = 1;

                }
            }


			glBegin(GL_QUADS);{
			    glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}
	}



}


void drawhorn()
{
    struct point points[100][100];
	int i,j;
	double h,r, horn_r;
	//generate points
	double radius = 11;
	int stacks = 89, slices = 89;
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		horn_r = 3*radius - 2*r;

		for(j=0;j<=slices;j++)
		{
			points[i][j].x=horn_r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].z=horn_r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].y=h+80;
		}
	}


	//draw quads using generated points
	int flag = 1;
	for(i=0;i<stacks;i++)
	{
        flag = 1;
		for(j=0;j<slices;j++)
		{
		    if(j%2==0)
            {
                if(flag)
                {
                    glColor3f(0,0,0);
                    flag = 0;
                }
                else
                {
                    glColor3f(0.9,0.9,0.9);
                    flag = 1;

                }
            }


			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);

			}glEnd();
		}
	}

}


void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
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

void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void drawCylinder(double radius,double height,int segments)
{
    int i, j;
    struct point points1[100];
    struct point points2[100];
    glColor3f(0.9,0.9,0.9);

    //generate points
    for(i=0;i<=segments;i++)
    {
        points1[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points1[i].z=radius*sin(((double)i/(double)segments)*2*pi);
        points1[i].y=0;
        points2[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points2[i].z=radius*sin(((double)i/(double)segments)*2*pi);
        points2[i].y=height;
    }

    int flag = 1;
    for(i=0;i<segments;i++)
		{
		    if(i%2==0)
            {
                if(flag)
                {
                    glColor3f(0,0,0);
                    flag = 0;
                }
                else
                {
                    glColor3f(0.9,0.9,0.9);
                    flag = 1;

                }


            }
			glBegin(GL_QUADS);{
			    glVertex3f(points1[i].x,points1[i].y,points1[i].z);
				glVertex3f(points2[i].x,points2[i].y,points2[i].z);
				glVertex3f(points2[i+1].x,points2[i+1].y,points2[i+1].z);
				glVertex3f(points1[i+1].x,points1[i+1].y,points1[i+1].z);

			}glEnd();
		}


}








void drawSS()
{

    /*glBegin(GL_LINES);{
        glColor3f(0,1,0);
        glVertex3f(gun_point.x,gun_point.y,gun_point.z);
        glVertex3f( gun_point.x+200.0*l_gun.x, gun_point.y+200.0*l_gun.y, gun_point.z+200.0*l_gun.z);
    }glEnd();*/


    glColor3f(1,0,0);
    drawPlane();



    for(int p = 0; p<gunshots; p++)
    {
        double x_value = shots[p][0];
        double z_value = shots[p][1];
        glColor3f(1,0,0);
        float lll = 4.0;
        glBegin(GL_QUADS);{
            glVertex3f( x_value+lll, 245,z_value+lll);
            glVertex3f( x_value+lll, 245,z_value-lll);
            glVertex3f( x_value-lll, 245,z_value-lll);
            glVertex3f( x_value-lll, 245,z_value+lll);
        }glEnd();

    }



    glColor3f(1,0,0);



    //glRotatef(theta_xy,u_gun.x,u_gun.y,u_gun.z);

    //glRotatef(theta_yz,r_gun.x,r_gun.y,r_gun.z);




    glPushMatrix();

    glRotatef(theta_xy,0,0,1);
    glTranslatef(0,30,0);
    boro_half_circle2();


    glPopMatrix();


    glRotatef(theta_xy,0,0,1);
    glRotatef(theta_yz,1,0,0);
    glTranslatef(0,30,0);

    boro_half_circle1();



    glRotatef(theta_gun,1,0,0);
    glRotatef(theta_xz,0,1,0);

    draw_half_circle();
    glTranslatef(0,11,0);

    drawCylinder(11,80,89);
    drawhorn();





}













void keyboardListener(unsigned char key, int x,int y){
    //print_my(l_gun);
	switch(key){

		case 'g':
			drawgrid=1-drawgrid;
			break;
        case '1':
        {
            l.x = l.x*cos(2*pi - 3*pi/180.0) + r.x*sin(2*pi - 3*pi/180.0);
            l.y = l.y*cos(2*pi - 3*pi/180.0) + r.y*sin(2*pi - 3*pi/180.0);
            l.z = l.z*cos(2*pi - 3*pi/180.0) + r.z*sin(2*pi - 3*pi/180.0);
            l = normalize(l);
            r = cross_product(l, u);
            r = normalize(r);
        }
        break;
        case '2':
        {
            l.x = l.x*cos(3*pi/180.0) + r.x*sin(3*pi/180.0);
            l.y = l.y*cos(3*pi/180.0) + r.y*sin(3*pi/180.0);
            l.z = l.z*cos(3*pi/180.0) + r.z*sin(3*pi/180.0);
            l = normalize(l);
            r = cross_product(l, u);
            r = normalize(r);
        }
        break;
        case '3':
        {
            l.x = l.x*cos(3*pi/180.0) + u.x*sin(3*pi/180.0);
            l.y = l.y*cos(3*pi/180.0) + u.y*sin(3*pi/180.0);
            l.z = l.z*cos(3*pi/180.0) + u.z*sin(3*pi/180.0);
            l = normalize(l);
            u = cross_product(r, l);
            u = normalize(u);
        }
        break;
        case '4':
        {
            l.x = l.x*cos(2*pi - 3*pi/180.0) + u.x*sin(2*pi - 3*pi/180.0);
            l.y = l.y*cos(2*pi - 3*pi/180.0) + u.y*sin(2*pi - 3*pi/180.0);
            l.z = l.z*cos(2*pi - 3*pi/180.0) + u.z*sin(2*pi - 3*pi/180.0);
            l = normalize(l);
            u = cross_product(r, l);
            u = normalize(u);
        }
        break;
        case '5':
        {
            u.x = u.x*cos(2*pi - 3*pi/180.0) + r.x*sin(2*pi - 3*pi/180.0);
            u.y = u.y*cos(2*pi - 3*pi/180.0) + r.y*sin(2*pi - 3*pi/180.0);
            u.z = u.z*cos(2*pi - 3*pi/180.0) + r.z*sin(2*pi - 3*pi/180.0);
            u = normalize(u);
            r = cross_product(l, u);
            r = normalize(r);
        }
        break;
        case '6':
        {
            u.x = u.x*cos(3*pi/180.0) + r.x*sin(3*pi/180.0);
            u.y = u.y*cos(3*pi/180.0) + r.y*sin(3*pi/180.0);
            u.z = u.z*cos(3*pi/180.0) + r.z*sin(3*pi/180.0);
            u = normalize(u);
            r = cross_product(l, u);
            r = normalize(r);
        }
        break;
        case 'q':
            if(theta_xy-30.0<0)
            {
                theta_xy += 1.0;

                struct point temp = {l_gun.x,l_gun.y,l_gun.z};
                l_gun.x = temp.x*cos(1.0*pi/180.0) - temp.y*sin(1.0*pi/180.0);
                l_gun.y = temp.y*cos(1.0*pi/180.0) + temp.x*sin(1.0*pi/180.0);
                l_gun = normalize(l_gun);


                temp = {gun_point.x,gun_point.y,gun_point.z};

                gun_point.x = temp.x*cos(1.0*pi/180.0) - temp.y*sin(1.0*pi/180.0);
                gun_point.y = temp.y*cos(1.0*pi/180.0) + temp.x*sin(1.0*pi/180.0);


                /*l_gun.x = l_gun.x*cos(2.0*pi - 1.0*pi/180.0) + r_gun.x*sin(2.0*pi - 1.0*pi/180.0);
                l_gun.y = l_gun.y*cos(2.0*pi - 1.0*pi/180.0) + r_gun.y*sin(2.0*pi - 1.0*pi/180.0);
                l_gun.z = l_gun.z*cos(2.0*pi - 1.0*pi/180.0) + r_gun.z*sin(2.0*pi - 1.0*pi/180.0);
                l_gun = normalize(l_gun);
                r_gun = cross_product(l_gun, u_gun);
                r_gun = normalize(r_gun);*/
            }
            break;
        case 'w':
            if(theta_xy+30.0>0)
            {
                theta_xy -= 1.0;

                struct point temp = {l_gun.x,l_gun.y,l_gun.z};
                l_gun.x = temp.x*cos(2.0*pi - 1.0*pi/180.0) - temp.y*sin(2.0*pi - 1.0*pi/180.0);
                l_gun.y = temp.y*cos(2.0*pi - 1.0*pi/180.0) + temp.x*sin(2.0*pi - 1.0*pi/180.0);

                l_gun = normalize(l_gun);


                temp = {gun_point.x,gun_point.y,gun_point.z};

                gun_point.x = temp.x*cos(2.0*pi - 1.0*pi/180.0) - temp.y*sin(2.0*pi - 1.0*pi/180.0);
                gun_point.y = temp.y*cos(2.0*pi - 1.0*pi/180.0) + temp.x*sin(2.0*pi - 1.0*pi/180.0);


                /*l_gun.x = l_gun.x*cos(1.0*pi/180.0) + r_gun.x*sin(1.0*pi/180.0);
                l_gun.y = l_gun.y*cos(1.0*pi/180.0) + r_gun.y*sin(1.0*pi/180.0);
                l_gun.z = l_gun.z*cos(1.0*pi/180.0) + r_gun.z*sin(1.0*pi/180.0);
                l_gun = normalize(l_gun);
                r_gun = cross_product(l_gun, u_gun);
                r_gun = normalize(r_gun);*/

            }
            break;
        case 'e':
            if(theta_yz-30.0<0)
            {
                theta_yz += 1.0;

                struct point temp = {l_gun.x,l_gun.y,l_gun.z};
                l_gun.y = temp.y*cos(1.0*pi/180.0) - temp.z*sin(1.0*pi/180.0);
                l_gun.z = temp.z*cos(1.0*pi/180.0) + temp.y*sin(1.0*pi/180.0);
                l_gun = normalize(l_gun);


                temp = {gun_point.x,gun_point.y,gun_point.z};

                gun_point.y = temp.y*cos(1.0*pi/180.0) - temp.z*sin(1.0*pi/180.0);
                gun_point.z = temp.z*cos(1.0*pi/180.0) + temp.y*sin(1.0*pi/180.0);


                /*l_gun.x = l_gun.x*cos(1.0*pi/180.0) + u_gun.x*sin(1.0*pi/180.0);
                l_gun.y = l_gun.y*cos(1.0*pi/180.0) + u_gun.y*sin(1.0*pi/180.0);
                l_gun.z = l_gun.z*cos(1.0*pi/180.0) + u_gun.z*sin(1.0*pi/180.0);
                l_gun = normalize(l_gun);
                u_gun = cross_product(r_gun, l_gun);
                u_gun = normalize(u_gun);*/


            }

            break;
        case 'r':
            if(theta_yz+30.0>0)
            {

                theta_yz -= 1.0;

                struct point temp = {l_gun.x,l_gun.y,l_gun.z};
                l_gun.y = temp.y*cos(2.0*pi - 1.0*pi/180.0) - temp.z*sin(2.0*pi - 1.0*pi/180.0);
                l_gun.z = temp.z*cos(2.0*pi - 1.0*pi/180.0) + temp.y*sin(2.0*pi - 1.0*pi/180.0);
                l_gun = normalize(l_gun);


                temp = {gun_point.x,gun_point.y,gun_point.z};

                gun_point.y = temp.y*cos(2.0*pi - 1.0*pi/180.0) - temp.z*sin(2.0*pi - 1.0*pi/180.0);
                gun_point.z = temp.z*cos(2.0*pi - 1.0*pi/180.0) + temp.y*sin(2.0*pi - 1.0*pi/180.0);




                /*l_gun.x = l_gun.x*cos(2.0*pi - 1.0*pi/180.0) + u_gun.x*sin(2.0*pi - 1.0*pi/180.0);
                l_gun.y = l_gun.y*cos(2.0*pi - 1.0*pi/180.0) + u_gun.y*sin(2.0*pi - 1.0*pi/180.0);
                l_gun.z = l_gun.z*cos(2.0*pi - 1.0*pi/180.0) + u_gun.z*sin(2.0*pi - 1.0*pi/180.0);
                l_gun = normalize(l_gun);
                u_gun = cross_product(r_gun, l_gun);
                u_gun = normalize(u_gun);*/

            }

            break;


        case 'd':
            if(theta_xz<30)
            {
                theta_xz += 1.0;

            }

            break;
        case 'f':
            if(theta_xz>-30)
            {
                theta_xz -= 1.0;

            }
            break;




        case 'a':
            if(theta_gun<30)
            {
                theta_gun += 1.0;


                struct point temp = {l_gun.x,l_gun.y,l_gun.z};
                l_gun.y = temp.y*cos(1.0*pi/180.0) - temp.z*sin(1.0*pi/180.0);
                l_gun.z = temp.z*cos(1.0*pi/180.0) + temp.y*sin(1.0*pi/180.0);
                l_gun = normalize(l_gun);

            }
            break;
        case 's':
            if(theta_gun>-30)
            {
                theta_gun -= 1.0;

                struct point temp = {l_gun.x,l_gun.y,l_gun.z};
                l_gun.y = temp.y*cos(2.0*pi - 1.0*pi/180.0) - temp.z*sin(2.0*pi - 1.0*pi/180.0);
                l_gun.z = temp.z*cos(2.0*pi - 1.0*pi/180.0) + temp.y*sin(2.0*pi - 1.0*pi/180.0);
                l_gun = normalize(l_gun);

            }
            break;

		default:
			break;


	}

	//print_my(l_gun);


}


void specialKeyListener(int key, int x,int y){
	switch(key){

		case GLUT_KEY_DOWN:		//down arrow key
			pos.x -= 2*l.x;
			pos.y -= 2*l.y;
			pos.z -= 2*l.z;
			break;
		case GLUT_KEY_UP:		// up arrow key
			pos.x += 2*l.x;
			pos.y += 2*l.y;
			pos.z += 2*l.z;
			break;

		case GLUT_KEY_RIGHT:
			pos.x += 2*r.x;
			pos.y += 2*r.y;
			pos.z += 2*r.z;
			break;
		case GLUT_KEY_LEFT:
			pos.x -= 2*r.x;
			pos.y -= 2*r.y;
			pos.z -= 2*r.z;
			break;

		case GLUT_KEY_PAGE_UP:
		    pos.x += 2*u.x;
			pos.y += 2*u.y;
			pos.z += 2*u.z;
			break;
		case GLUT_KEY_PAGE_DOWN:
			pos.x -= 2*u.x;
			pos.y -= 2*u.y;
			pos.z -= 2*u.z;
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP

				double z_value = (250-gun_point.y)*(l_gun.z/l_gun.y);
				double x_value = (250-gun_point.y)*(l_gun.x/l_gun.y);
				if(x_value<=110 && x_value>=-110 && z_value<=110 && z_value>=-110)
                {
                    shots[gunshots][0] = x_value;
                    shots[gunshots][1] = z_value;
                    gunshots++;
                    cout<<"GUNSHOT"<<endl;
                }
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			if(state == GLUT_DOWN)
            {
                drawaxes=1-drawaxes;

			}
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

	gluLookAt(pos.x,pos.y,pos.z,	pos.x+l.x,pos.y+l.y,pos.z+l.z,	u.x,u.y,u.z);
	//gluLookAt(pos.x,pos.y,pos.z,	0,0,0,	0,0,1);
    glMatrixMode(GL_MODELVIEW);


	drawAxes();
	drawGrid();


    drawSS();

	glutSwapBuffers();
}


void animate(){
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	angle=0;
	theta_xy = 0;
	theta_yz = 0;
	theta_xz = 0;

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

	glutCreateWindow("My OpenGL Program");

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















