#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
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
    vector<int> a(N);
    repeat(i, N) cin >> a[i];
    int Q;
    cin >> Q;
    vector<int> x(Q), y(Q);
    repeat(i, Q) {
        cin >> x[i] >> y[i];
        --x[i], --y[i];
    }

    vector<int> b = a;
    sort(b.begin(), b.end());
    int nokori = 0;
    repeat(i, N) {
        if (a[i] != b[i]) ++nokori;
    }

    int res = 0;
    while (res < Q) {
        if (nokori == 0) break;
        int px = x[res], py = y[res];
        int diff = 0;
        if (a[px] != b[px]) --diff;
        if (a[py] != b[py]) --diff;
        swap(a[px], a[py]);
        if (a[px] != b[px]) ++diff;
        if (a[py] != b[py]) ++diff;
        nokori += diff;
        ++res;
    }
    if (nokori)
        cout << -1 << endl;
    else
        cout << res << endl;
    return 0;
}