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

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> a(N);
    repeat(i, N) a[i] = i;
    set<pair<int, int>> inv;
    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        --x, --y;
        if (t == 1) {
            swap(a[x], a[x + 1]);
            if (a[x] > a[x + 1]) {
                inv.emplace(x, x + 1);
            } else {
                auto itr = inv.find({x, x + 1});
                assert(itr != inv.end());
                inv.erase(itr);
            }
            if (0 <= x - 1) {
                if (a[x - 1] < a[x] && a[x - 1] > a[x + 1]) {
                    auto itr = inv.find({x - 1, x});
                    assert(itr != inv.end());
                    inv.erase(itr);
                }
                if (a[x - 1] > a[x] && a[x - 1] < a[x + 1]) {
                    inv.emplace(x - 1, x);
                }
            }
            if (x + 2 < N) {
                if (a[x + 1] > a[x + 2] && a[x] < a[x + 2]) {
                    inv.emplace(x + 1, x + 2);
                }
                if (a[x + 1] < a[x + 2] && a[x] > a[x + 2]) {
                    auto itr = inv.find({x + 1, x + 2});
                    assert(itr != inv.end());
                    inv.erase(itr);
                }
            }
        } else {
            bool l = (0 <= x - 1 ? a[x - 1] < a[x] : false);
            bool r = (y + 1 < N ? a[y] < a[y + 1] : false);
            sort(a.begin() + x, a.begin() + y + 1);
            // [x, y]の両隣で転倒数の変化がないか調べる
            auto itr = inv.lower_bound({x, x + 1});
            while (itr != inv.end() && itr->second <= y) {
                inv.erase(itr++);
            }
            if (0 <= x - 1) {
                if (l) {
                    if (a[x - 1] > a[x]) {
                        inv.emplace(x - 1, x);
                    }
                } else {
                    if (a[x - 1] < a[x]) {
                        auto itr = inv.find({x - 1, x});
                        assert(itr != inv.end());
                        inv.erase(itr);
                    }
                }
            }
            if (y + 1 < N) {
                if (r) {
                    if (a[y] > a[y + 1]) {
                        inv.emplace(y, y + 1);
                    }
                } else {
                    if (a[y] < a[y + 1]) {
                        auto itr = inv.find({y, y + 1});
                        assert(itr != inv.end());
                        inv.erase(itr);
                    }
                }
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