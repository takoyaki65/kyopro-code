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

// K <= 7なので、全探索
int main() {
    int A, B, C, K;
    cin >> A >> B >> C >> K;
    for (int b = 0; b <= K; ++b) {
        for (int c = 0; b + c <= K; ++c) {
            if (A < (B << b) && (B << b) < (C << c)) {
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
    return 0;
}