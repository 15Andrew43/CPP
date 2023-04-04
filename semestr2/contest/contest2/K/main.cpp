#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    int Hp, p;
    int Hs, s;
    std::cin >> p >> Hp >> s >> Hs;

    if ((float)s/p >= float(Hs)/Hp || Hs < Hp) {
        std::cout << std::fixed << std::setprecision(7) << 0.0;
    } else if (s > p) {
        double x = sqrt((Hs-Hp)*(Hs-Hp) - (s-p)*(s-p));
        double tg = x / (s-p);
        double y = x * p / (s-p);
        double z = sqrt(p*p + y*y) - Hp;
        double L = (s-p) * z / x;
        std::cout << std::fixed << std::setprecision(7) << L;
    } else if (s == p) {
        std::cout << std::fixed << std::setprecision(7) << p;
    } else if (s < p) {
        double x = sqrt((Hs-Hp)*(Hs-Hp) - (s-p)*(s-p));
        double tg = x / (p-s);
        double y = p * x / (p-s);
        double z = sqrt(p*p + y*y);
        double L = (p-s) * (z + Hp) / x;
        std::cout << std::fixed << std::setprecision(7) << L;
    }
}