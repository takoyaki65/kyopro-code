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
    int N;
    cin >> N;
    vector<long> L(N);
    repeat(i, N) cin >> L[i];
    sort(L.begin(), L.end());
    long res = 0L;
    repeat(i, N) {
        repeat_from(j, i + 1, N) {
            if (L[i] == L[j]) continue;
            repeat_from(k, j + 1, N) {
                if (L[j] == L[k] || L[i] + L[j] <= L[k]) continue;
                ++res;
            }
        }
    }
    cout << res << endl;
    return 0;
}