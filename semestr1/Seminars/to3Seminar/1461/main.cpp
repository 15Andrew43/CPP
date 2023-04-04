#include <iostream>

using namespace std;

int main(){
    int n, ans = 0, count = 1;
    cin >> n;
    int Balls[n+2];
    Balls[0]=-1;
    for(int i = 1; i < n+1; ++i){
        cin >> Balls[i];
    }
    Balls[n+1]=-1;

    int L=0, R=0;

    for (int i = 0; i < n+1; ++i){
        if (Balls[i] == Balls[i+1])
            count++;
        else{
            if (count >= 3){
                R = i + 1;
                L = i - count;
                break;
            }
            count = 1;
        }
    }

    while (L >= 1 && R <= n && Balls[L]==Balls[R]) {
        cout << "L " << L << "  R " << R << endl;
        // нужно учесть count :(
        if (Balls[L] == Balls[L - 1] || Balls[R] == Balls[R + 1]) {
            if (Balls[R] == Balls[R + 1]) {
                R++;
            }
            if (Balls[L] == Balls[L - 1]) {
                L--;
            }
        }
        else{
            L--;
            R++;
        }
    }
    cout << "L " << L << "  R " << R << endl;

    if (R==0){
        ans = 0;
    }
    else {
        ans = R - L - 1;
    }
    cout << ans << endl;
    return 0;
}
