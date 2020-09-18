#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
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

// 2*x + 3*y + 4*z = M
// x + y + z = N
// y + 2*z = M - 2*N

int main() {
    int N, M;
    cin >> N >> M;
    for (int z = 0; z <= N && 4 * z <= M && 2 * z <= M - 2 * N; ++z) {
        int y = M - 2 * N - 2 * z;
        int x = N - y - z;
        /*         cout << x << " " << y << " " << z << " "
             << ": " << 2 * x + 3 * y + 4 * z << endl;
 */
        if (x < 0 || y < 0) continue;
        if (2 * x + 3 * y + 4 * z == M) {
            cout << x << " " << y << " " << z << endl;
            return 0;
        }
    }
    cout << "-1 -1 -1" << endl;
    return 0;
}