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
    int N;
    cin >> N;
    V<int> A(N, 0);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    long long ans = 1000;
    for (int i = 0; i < N - 1; ++i) {
        if (A[i] < A[i + 1]) {
            ans = ans / A[i] * A[i + 1] + ans % A[i];
        }
    }
    cout << ans << endl;
    return 0;
}