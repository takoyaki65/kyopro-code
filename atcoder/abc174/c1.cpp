#include <bits/stdc++.h>
//https://qiita.com/ysuzuki19/items/d89057d65284ba1a16ac
#define debug(var)                  \
    do {                            \
        std::cout << #var << " : "; \
        view(var);                  \
    } while (0)
template <typename T>
void view(T e) { std::cout << e << std::endl; }

template <typename T>
void view(const std::vector<T>& v) {
    for (const auto& e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void view(const std::vector<std::vector<T>>& vv) {
    for (const auto& v : vv) {
        view(v);
    }
}

using namespace std;
//yosupo
template <class T>
using V = vector<T>;
template <class T>
using VV = V<V<T>>;

int main() {
    int K;
    cin >> K;
    if (K % 2 == 0 || K % 5 == 0) {
        cout << -1 << endl;
        return 0;
    }
    int L = K % 7 == 0 ? 9 * K / 7 : 9 * K;
    int res = 1;
    int Mod = 10 % L;
    int Max = 90000000;
    while (Max--) {
        if (Mod == 1) {
            cout << res << endl;
            return 0;
        }
        Mod = (Mod * 10) % L;
        ++res;
    }
    return 0;
}