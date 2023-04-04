#include <iostream>
#include <vector>

using namespace std;

int g(int a, int b);

int main() {
    int a, b;
    cin >> a >> b;
    cout << g(a, b)<< endl;
    cout << "Hello, World!" << endl;
    return 0;
}

int g(int a, int b)
{
    while (a % b != 0)
    {
        a = a % b;
        swap(a, b);
    }
    return b;
}

vector<bool> Eratosfen(int n)
{
    vector<bool>v[n];
    for (int i=2; i<n; ++i)
    {
        if (v[i])
            int j=i;
            while (j <= n)
            {
                j+=i;
                v[j]=false;
            }
    }
}

// vector<int> resh()