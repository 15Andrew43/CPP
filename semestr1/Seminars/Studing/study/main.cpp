#include <iostream>
using namespace std;

int school=1543;

int g();
int f();

int main() {

    cout << school++ << "function main()" << endl;
    cout << f();
    float a, b;
    cin >> a >> b;
    cout << a/b << endl;


    float  q=4.9E-324;
    double Q=4.9E-324;
    short int j = -32768;    // [-2^15, 2^15-1]
    unsigned short int J = 65535;   // [0, 2^16-1]
    int I = -2147483648;     // [-2^31, 2^31-1]
    unsigned int i = 4294967295;    // [0, 2^32-1]
    long int t = 9223372036854775807;   // [-2^63, 2^63-1]

//  беззнаковое/знаковое число, как ставится знак...
    short int u;
    short unsigned int U;
    U=65533;
    u=U;
    cout <<"\n" << U << " != " << u << endl;


    cout << q << " " << Q;
    cout << "Hello, W\norl\nd!" << std::endl;
    return 0;
}
int g(int a)
{
    cout << school++ << "function g(x)" << endl;
    return a*a;
}

int f()
{
    string school = "best school\n";

    cout << ::school++ << school << "function f(X)" << endl;
    int a=5;
    return g(a);
}
