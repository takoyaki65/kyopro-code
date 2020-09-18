#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
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

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N);
    repeat(i, N) a[i] = i;
    set<int> inv;  // a[x] > a[x+1]
    auto Swap = [&](int x) -> void {
        swap(a[x], a[x + 1]);
        if (a[x] > a[x + 1]) {
            inv.emplace(x);
        } else {
            inv.erase(x);
        }
        if (0 < x) {
            if (inv.count(x - 1) and a[x - 1] < a[x])
                inv.erase(x - 1);
            else if (!inv.count(x - 1) and a[x - 1] > a[x])
                inv.insert(x - 1);
        }
        if (x < N - 2) {
            if (inv.count(x + 1) and a[x + 1] < a[x + 2])
                inv.erase(x + 1);
            else if (!inv.count(x + 1) and a[x + 1] > a[x + 2])
                inv.insert(x + 1);
        }
    };
    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        --x, --y;
        if (t == 1) {
            Swap(x);
        } else {
            while (true) {
                auto itr = inv.lower_bound(x);
                if (itr == end(inv) or *itr >= y) break;
                Swap(*itr);
            }
        }
        /*         for (int x : a) cout << x + 1 << " ";
        cout << endl;
        cout << "inv: ";
        for (auto pp : inv) cout << "(" << pp.first + 1 << ", " << pp.second + 1 << ")"
                                 << " ";
        cout << endl;
 */
    }
    repeat(i, N) {
        cout << a[i] + 1 << (i == N - 1 ? "\n" : " ");
    }
    return 0;
}