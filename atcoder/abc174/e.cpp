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
    int N, K;
    cin >> N >> K;
    V<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    auto b_search = [](V<int>& v, int k) -> int {
        int ng = 0, ok = 1000000010;
        //int Iteration_num = 0;
        while (abs(ok - ng) > 1) {
            //debug(ng);
            //debug(ok);
            int mid = (ng + ok) / 2;
            long long s = 0;
            for (int Ai : v) {
                s += ((long long)Ai + mid - 1) / mid - 1;
            }
            if (s > k)
                ng = mid;
            else
                ok = mid;
            //debug(mid);
            //debug(s);
            //++Iteration_num;
        }
        //cout << Iteration_num << endl;
        return ok;
    };

    cout << b_search(A, K) << endl;
    return 0;
}