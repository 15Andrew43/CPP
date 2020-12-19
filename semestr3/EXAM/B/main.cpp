/*
 Дана строка S, состоящая из N символов. Определим функцию A(i) от первых i символов этой сроки следующим образом: A(i) = максимально возможному k, что равны следующие строки: S[1] + S[2] + S[3] + … + S[k] и S[i] + S[i - 1] + S[i - 2] + … +S[i - k + 1], где S[i] — i-й символ строки S, а знак «+» означает, что символы записываются в строчку непосредственно друг за другом.

Напишите программу, которая вычислит значения функции A для заданной строчки для всех возможных значений i от 1 до N.

Формат ввода
В первой строке входного файла записано одно число N (1 ≤ N ≤ 2 ⋅ 105). Во второй строке записана строка длиной N символов, состоящая только из больших и/или маленьких латинских букв.

Формат вывода
В выходной файл выведите N чисел — значения функции A(1), A(2), …, A(N).

Пример
Ввод	Вывод
5
aabaa
1 2 0 1 5
 */

#include <iostream>
#include <vector>


std::vector<int> z_function(const std::string& s) {
    std::vector<int> z(s.length(), 0);
    for (int i = 1, l = 0, r = 0; i < s.length(); i++) {
        if (i <= r) {
            z[i] = std::min(z[i - l], r - i + 1);
        }
        while (i + z[i] < s.length()) {
            if (s[i + z[i]] == s[z[i]]) {
                z[i]++;
            } else {
                break;
            }
        }
        if (z[i] > 0 && i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

std::string Reverse(const std::string& str) {
    std::string new_str = str;
    for (int i = 0; i < str.size()/2; ++i) {
        std::swap(new_str[i], new_str[str.size() - 1 - i]);
    }
    return new_str;
}

std::vector<int> A_function(const std::string& str) {
    std::string new_str = str + '$' + Reverse(str);
    auto z = z_function(new_str);

    std::vector<int> res;
    for (int i = z.size()-1; i > z.size() - 1 - str.size(); --i) {
        res.push_back(z[i]);
    }
    return res;
}


int main() {
    std::string str;
    int n;
    std::cin >> n >> str;

    for (auto x: A_function(str)) {
        std::cout << x << ' ';
    }
    return 0;
}