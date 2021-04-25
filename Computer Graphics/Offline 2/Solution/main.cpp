#include <bits/stdc++.h>

using namespace std;

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

    friend ostream &operator<<(ostream &os, const point &p)
    {
        os << p.x << " " << p.y << " " << p.z << endl;
        return os;
    }
};

int main()
{

    cout << "Hello World" << endl;

    freopen("scene.txt", "r", stdin);

    double x, y, z;
    cin >> x >> y >> z;
    point eye = point(x, y, z);
    cin >> x >> y >> z;
    point look = point(x, y, z);
    cin >> x >> y >> z;
    point up = point(x, y, z);

    cout << eye;
    cout << look;
    cout << up;

    double fovY, aspectRatio, near, far;
    cin >> fovY >> aspectRatio >> near >> far;

    return 0;
}