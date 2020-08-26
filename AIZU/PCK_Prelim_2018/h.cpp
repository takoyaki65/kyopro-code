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

int main() {
    int N;
    cin >> N;
    auto C = vectors(-1, N, 0);
    repeat(i, N) {
        int M;
        cin >> M;
        C[i].resize(M);
        repeat(j, M) {
            cin >> C[i][j];
        }
    }
    vector<int> Num;
    repeat(i, N) {
        sort(C[i].rbegin(), C[i].rend());
        repeat(j, min(i + 1, (int)C[i].size())) {
            Num.push_back(C[i][j]);
        }
    }
    sort(Num.rbegin(), Num.rend());
    long long res = 0LL;
    repeat(i, N) res += (long long)Num[i];
    cout << res << endl;
    return 0;
}