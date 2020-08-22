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
    int N, Q;
    cin >> N >> Q;
    vector<int> below_container(N, -1), top_desk(N);
    repeat(i, N) top_desk[i] = i;
    while (Q--) {
        int f, t, x;
        cin >> f >> t >> x;
        --f, --x, --t;
        int f_top = top_desk[f];
        top_desk[f] = below_container[x];
        below_container[x] = top_desk[t];
        top_desk[t] = f_top;
    }
    vector<int> ans(N, -1);
    repeat(i, N) {
        int cur = top_desk[i];
        while (cur != -1) {
            ans[cur] = i;
            cur = below_container[cur];
        }
    }
    for (int t : ans) cout << t + 1 << endl;
    return 0;
}