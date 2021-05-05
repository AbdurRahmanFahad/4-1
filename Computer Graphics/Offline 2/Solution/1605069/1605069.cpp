#include <bits/stdc++.h>
#include "bitmap_image.hpp"

using namespace std;

/***************** Global Variables *****************/
point eye, look, up;
double fovX, fovY, aspectRatio, near, far, t, r;
point l, rr, u;
/***************** Point Related *****************/

class point
{
public:
    double x, y, z;

    point()
    {
        x = y = z = 0.0;
    }

    point(float a, float b, float c)
    {
        x = a, y = b, z = c;
    }

    point operator+(point &p)
    {
        point res = point(x + p.x, y + p.y, z + p.z);
        return res;
    }

    point operator-(point &p)
    {
        point res = point(x - p.x, y - p.y, z - p.z);
        return res;
    }

    point operator*(double d)
    {
        point res;
        res.x = x * d, res.y = y * d, res.z = z * d;
        return res;
    }

    friend ostream &operator<<(ostream &os, point &p)
    {
        os << p.x << " " << p.y << " " << p.z << endl;
        return os;
    }
};

double dot(point p1, point p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

point cross(point a, point b)
{
    point res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    return res;
}

point normalize(point p)
{
    point res;
    double val = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
    res.x = p.x / val, res.y = p.y / val, res.z = p.z / val;
    return res;
}

/***************** Matrix Related *****************/

point rotation_Rodrigues(point x, point a, double theta);

class matrix
{
public:
    double mat[4][4] = {0};

    matrix translation_matrix(double a, double b, double c)
    {
        matrix res;
        res.mat[0][0] = res.mat[1][1] = res.mat[2][2] = res.mat[3][3] = 1;
        res.mat[0][3] = a;
        res.mat[1][3] = b;
        res.mat[2][3] = c;
        return res;
    }

    matrix scaling_matrix(double a, double b, double c)
    {
        matrix res;
        res.mat[0][0] = a;
        res.mat[1][1] = b;
        res.mat[2][2] = c;
        res.mat[3][3] = 1;
        return res;
    }

    matrix projection_matrix(double near, double far, double r, double t)
    {
        matrix res;
        res.mat[0][0] = near / r;
        res.mat[1][1] = near / t;
        res.mat[2][2] = -(far + near) / (far - near);
        res.mat[2][3] = -(2 * far * near) / (far - near);
        res.mat[3][2] = -1;
        return res;
    }

    matrix rotation_matrix(point a, double angle)
    {
        matrix res;
        res.mat[3][3] = 1;

        point i = point(1, 0, 0);
        point j = point(0, 1, 0);
        point k = point(0, 0, 1);

        point p = rotation_Rodrigues(i, a, angle);
        point q = rotation_Rodrigues(j, a, angle);
        point r = rotation_Rodrigues(k, a, angle);

        res.mat[0][0] = p.x, res.mat[1][0] = p.y, res.mat[2][0] = p.z;
        res.mat[0][1] = q.x, res.mat[1][1] = q.y, res.mat[2][1] = q.z;
        res.mat[0][2] = r.x, res.mat[1][2] = r.y, res.mat[2][2] = r.z;

        return res;
    }

    friend ostream &
    operator<<(ostream &os, matrix &m)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
                os << m.mat[i][j] << " ";

            os << endl;
        }
        return os;
    }
};

/***************** Other Function *****************/

point rotation_Rodrigues(point x, point a, double theta)
{
    point res;
    double cos_theta, sin_theta;
    theta = theta * acos(-1.0) / 180.0;
    cos_theta = cos(theta);
    sin_theta = sin(theta);

    res = (x * cos_theta);
    res = (a * ((1 - cos_theta) * dot(a, x))) + res;
    res = cross(a, x) * sin_theta + res;

    return res;
}

matrix mul(matrix a, matrix b)
{
    matrix c;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }

    return c;
}

matrix mul2(matrix a, point b)
{
    matrix B;
    B.mat[0][0] = b.x, B.mat[1][0] = b.y, B.mat[2][0] = b.z;
    B.mat[3][0] = 1;
    return mul(a, B);
}

point transform(matrix m, point p)
{
    point res;
    m = mul2(m, p);
    res.x = m.mat[0][0] / m.mat[3][0];
    res.y = m.mat[1][0] / m.mat[3][0];
    res.z = m.mat[2][0] / m.mat[3][0];
    return res;
}

/***************** Main Function *****************/

int main()
{

    freopen("scene.txt", "r", stdin);
    ofstream stage1, stage2, stage3, debug;
    stage1.open("stage1.txt");
    stage2.open("stage2.txt");
    stage3.open("stage3.txt");
    debug.open("debug.txt");

    double x, y, z;
    cin >> x >> y >> z;
    eye = point(x, y, z);
    cin >> x >> y >> z;
    look = point(x, y, z);
    cin >> x >> y >> z;
    up = point(x, y, z);

    cin >> fovY >> aspectRatio >> near >> far;

        l = look - eye;
    l = normalize(l);
    rr = cross(l, up);
    rr = normalize(rr);
    u = cross(rr, l);

    fovX = fovY * aspectRatio;
    fovX = fovX * acos(-1.0) / 180.0;
    fovY = fovY * acos(-1.0) / 180.0;
    t = near * tan(fovY / 2);
    r = near * tan(fovX / 2);

    // INIT *******************************************
    matrix trans = trans.translation_matrix(-eye.x, -eye.y, -eye.z);
    matrix rot;
    rot.mat[0][0] = rr.x, rot.mat[0][1] = rr.y, rot.mat[0][2] = rr.z;
    rot.mat[1][0] = u.x, rot.mat[1][1] = u.y, rot.mat[1][2] = u.z;
    rot.mat[2][0] = -l.x, rot.mat[2][1] = -l.y, rot.mat[2][2] = -l.z;
    rot.mat[3][3] = 1;

    // V = RT
    matrix view_transformation = mul(rot, trans);

    matrix projection_mat = projection_mat.projection_matrix(near, far, r, t);

    // Input ******************************************

    string command;
    stack<matrix> S;
    stack<stack<matrix>> State;
    matrix initial;
    initial.mat[0][0] = initial.mat[3][3] = initial.mat[1][1] = initial.mat[2][2] = 1;
    S.push(initial);

    while (1)
    {
        cin >> command;

        if (command == "end")
            break;

        if (command == "triangle")
        {
            point triangle[3];
            double a, b, c;

            for (int i = 0; i < 3; i++)
            {
                cin >> a >> b >> c;
                triangle[i] = point(a, b, c);
            }

            point model, view, projection;

            for (int i = 0; i < 3; i++)
            {
                model = transform(S.top(), triangle[i]);
                view = transform(view_transformation, model);
                projection = transform(projection_mat, view);

                //debug << view_transformation << endl;
                stage1 << model;
                stage2 << view;
                stage3 << projection;
            }

            stage1 << endl;
            stage2 << endl;
            stage3 << endl;
        }
        else if (command == "translate")
        {
            double a, b, c;
            cin >> a >> b >> c;
            matrix m = m.translation_matrix(a, b, c);
            S.push(mul(S.top(), m));
        }
        else if (command == "scale")
        {
            double a, b, c;
            cin >> a >> b >> c;
            matrix m = m.scaling_matrix(a, b, c);
            S.push(mul(S.top(), m));
        }
        else if (command == "rotate")
        {
            double a, b, c, angle;
            cin >> angle >> a >> b >> c;
            point temp = point(a, b, c);
            temp = normalize(temp);
            matrix m = m.rotation_matrix(temp, angle);
            S.push(mul(S.top(), m));
        }
        else if (command == "push")
        {
            State.push(S);
        }
        else if (command == "pop")
        {
            S = State.top();
            State.pop();
        }
    }

    return 0;
}