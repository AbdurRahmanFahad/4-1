#include <bits/stdc++.h>

using namespace std;

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
        point res = point(x + p.x, y + p.y, z + p.y);
        return res;
    }

    point operator-(point &p)
    {
        point res = point(x - p.x, y - p.y, z - p.y);
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

    matrix rotation_matrix()
    {
        matrix res;
        res.mat[3][3] = 1;
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

/***************** Main Function *****************/

int main()
{

    freopen("scene.txt", "r", stdin);

    double x, y, z;
    cin >> x >> y >> z;
    point eye = point(x, y, z);
    cin >> x >> y >> z;
    point look = point(x, y, z);
    cin >> x >> y >> z;
    point up = point(x, y, z);

    // cout << eye;
    // cout << look;
    // cout << up;

    double fovX, fovY, aspectRatio, near, far, t, r;
    cin >> fovY >> aspectRatio >> near >> far;

    point l, rr, u;
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

    string command;

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
        }
        else if (command == "translate")
        {
            double a, b, c;
            cin >> a >> b >> c;
            ///TODO: translate it
        }
        else if (command == "scale")
        {
            double a, b, c;
            cin >> a >> b >> c;
        }
        else if (command == "rotate")
        {
            double a, b, c, angle;
            cin >> angle >> a >> b >> c;
        }
        else if (command == "push")
        {
            ///TODO: push
        }
        else if (command == "pop")
        {
            ///TODO: pop
        }
    }

    return 0;
}