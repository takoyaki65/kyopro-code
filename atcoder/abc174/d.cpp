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

// 入れ替えるときは必ず違う色同士にする

int main() {
    int N;
    string C;
    cin >> N >> C;

    int Left = 0, Right = C.size() - 1;
    int res = 0;
    while (Left < Right) {
        while (Left < N && C[Left] != 'W') ++Left;
        while (Right >= 0 && C[Right] != 'R') --Right;
        if (Right <= Left || Left >= N || Right < 0) break;
        swap(C[Left], C[Right]);
        ++res;
    }
    //cout << C << endl;
    cout << res << endl;
    return 0;
}