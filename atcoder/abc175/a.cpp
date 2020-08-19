#include <algorithm>
#include <iostream>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

int main() {
    string S;
    cin >> S;
    int res = 0;
    repeat(i, S.size()) {
        if (S[i] == 'R') {
            int tmp = 0;
            repeat_from(j, i, S.size()) {
                if (S[j] != 'R') break;
                ++tmp;
            }
            setmax(res, tmp);
        }
    }
    cout << res << endl;
    return 0;
}