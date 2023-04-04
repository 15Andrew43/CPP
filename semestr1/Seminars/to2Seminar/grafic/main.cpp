#include <iostream>
#include <cmath>

using namespace std;

void Triangle1(int n);
void Triangle2(int n);
void Triangle3(int n);
void Rhombus1(int n);
void Rhombus2(int n);
void Circle(int n);
void Ring(int n);
void Smile(int n);
void Chess(int n);

int main() {
    int a, n;
    cout << "Что хотите нарисовать?\n1. Triangle-1\n2. Triangle-2\n3. Triangle-3\n4. Rhombus-1\n5. Rhombus-2\n6. Circle\n7. Ring\n8. Smile\n9. Chess\n";

    cin >> a;
    cout << "размеры фигуры: ";
    cin >> n;
    cout << endl;

    switch (a)
    {
        case 1:
            Triangle1(n);
            break;
        case 2:
            Triangle2(n);
            break;
        case 3:
            Triangle3(n);
            break;
        case 4:
            Rhombus1(n);
            break;
        case 5:
            Rhombus2(n);
            break;
        case 6:
            Circle(n);
            break;
        case 7:
            Ring(n);
            break;
        case 8:
            Smile(n);
            break;
        case 9:
            Chess(n);
            break;
    }

    return 0;
}

void Triangle1(int n)
{
    for (int y=n-1; y>=0; --y)
    {
        for (int x=0; x<n; ++x)
        {
            if (y <= -x+n-1)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Triangle2(int n)
{
    for (int y=n-1; y>=0; --y)
    {
        for (int x=0; x<2*n-3; ++x)
        {
            if (y <= -x+(2*n-3) &&
                y <= x &&
                (x + y) % 2 == 0)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Triangle3(int n)
{
    for (int y=n-1; y>=0; --y)
    {
        for (int x=0; x<2*n-3; ++x)
        {
            if (y < -x+(2*n-3) && y <= x)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Rhombus1(int n)
{
    for (int y=n-1; y>=0; --y)
    {
        for (int x=0; x<n; ++x)
        {
            if (y <= x+n/2 &&
                y <= -x+n/2*3 &&
                y >= -x+n/2 &&
                y >= x-n/2)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Rhombus2(int n)
{
    for (int y=n-1; y>=0; --y)
    {
        for (int x=0; x<n; ++x)
        {
            if (y == x+n/2 ||
                y == -x+n/2*3 ||
                y == -x+n/2 ||
                y == x-n/2)
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Circle(int n)
{
    float N;
    int R;
    R=n/2;
    N=R-0.5;
    for (int y=2*R-1; y>=0; --y)
    {
        for (int x=0; x<2*R; ++x)
        {
            if ((x-N)*(x-N)+(y-N)*(y-N) <= R*R)
                cout << "**";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

void Ring(int n)
{
    float N;
    int R;
    R=n/2;
    N=R-0.5;
    for (int y=2*R-1; y>=0; --y)
    {
        for (int x=0; x<2*R; ++x)
        {
            if ((x-N)*(x-N)+(y-N)*(y-N) <= R*R &&
                ((x-N)*(x-N)+(y-N)*(y-N) >= (R-1)*(R-1)))
                cout << "**";
            else
                cout << "  ";
        }
        cout << endl;
    }
}

void Smile(int n)  // только для чисел больших 10
{
    for (int y=n; y>=0; --y)
    {
        for (int x=0; x<n; ++x)
        {
            if (y == n || y == 0 || x == n-1 || x == 0 || // контур головы
                    (x == n/2 && y >= n/3 && y <= 2*n/3) || (y == n/3 && x<=n/2 && x >= n/2-n/5) || // нос
                    (x > n/8 && x <= 3*n/8 && y <= 7*n/8 && y >= 5*n/8) || // левый глаз
                    (x >= 5*n/8 && x < 7*n/8 && y <= 7*n/8 && y >= 5*n/8) || // правый глаз
                    (x > n/8 && x < 7*n/8  && y == n/8) || (x == n/8 && y >= n/8 && y <= n/5)) // рот
                cout << "*";
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Chess(int n) // работает только для чисел кратных 8
{
    int a = n/8;
    for (int y = n-1; y >= 0; --y)
    {
        for (int x = 0; x < n; ++x)
        {
            if ((x/a+y/a)%2 == 0)
                cout << "**";
            else
                cout << "  ";
        }
        cout << endl;
    }
}