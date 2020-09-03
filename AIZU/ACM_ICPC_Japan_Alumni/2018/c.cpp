#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

int a, b, c, d;

#define PRINT(X) cout << #X << " " << X << endl;

int parse(string &str, int &cur) {
    if (str[cur] >= 'a' && str[cur] <= 'd') {
        if (str[cur] == 'a') {
            ++cur;
            return a;
        } else if (str[cur] == 'b') {
            ++cur;
            return b;
        } else if (str[cur] == 'c') {
            ++cur;
            return c;
        } else {
            ++cur;
            return d;
        }
    } else if (str[cur] == '[') {
        int res = parse(str, ++cur);
        ++cur;
        return res;
    } else {
        char op = str[cur];
        int x = parse(str, ++cur);
        int y = parse(str, cur);
        if (op == '+') {
            return x | y;
        } else if (op == '*') {
            return x & y;
        } else {
            return x ^ y;
        }
    }
}

int main() {
    string str, num;
    while (cin >> str, str != ".") {
        cin >> num;
        a = num[0] - '0';
        b = num[1] - '0';
        c = num[2] - '0';
        d = num[3] - '0';
        /*         PRINT(a);
        PRINT(b);
        PRINT(c);
        PRINT(d); */
        int cur = 0;
        int Hash = parse(str, cur);
        int ans = 0;
        for (a = 0; a <= 9; ++a) {
            for (b = 0; b <= 9; ++b) {
                for (c = 0; c <= 9; ++c) {
                    for (d = 0; d <= 9; ++d) {
                        cur = 0;
                        if (parse(str, cur) == Hash) ++ans;
                    }
                }
            }
        }

        cout << Hash << " " << ans << endl;
    }
    return 0;
}