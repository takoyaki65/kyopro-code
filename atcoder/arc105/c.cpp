#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> w(N);
    repeat(i, N) cin >> w[i];
    vector<pair<int, int>> vl(M);
    repeat(i, M) {
        cin >> vl[i].second >> vl[i].first;
    }
    sort(begin(vl), end(vl));

    {
        int maxW = *max_element(begin(w), end(w));
        repeat(i, M) {
            if (maxW > vl[i].first) {
                cout << -1 << endl;
                return 0;
            }
        }
    }

    vector<pair<int, int>> border;
    border.emplace_back(0, 0);
    {
        int maxL = 0;
        int cur = 0;
        while (cur < M) {
            int L = vl[cur].second;
            int barV = vl[cur].first;
            while (++cur < M and vl[cur].first == barV) {
                setmax(L, vl[cur].second);
            }
            if (maxL < L) {
                border.emplace_back(barV, L);
                maxL = L;
            }
        }
    }
    /*     for (auto bvl : border) {
        cout << bvl.first << " : " << bvl.second << endl;
    }
 */
    int res = numeric_limits<int>::max();
    vector<int> perm(N);
    iota(begin(perm), end(perm), 0);
    do {
        vector<int> d(N);
        repeat(j, N) {
            repeat(i, j) {
                int ws = 0;
                repeat_from(k, i, j + 1) ws += w[perm[k]];

                // ws未満
                int it = lower_bound(begin(border), end(border), make_pair(ws, -1)) - begin(border);
                assert(it - 1 >= 0);
                int minL = border[it - 1].second;
                //cout << i << " -> " << j << " ws: " << ws << " minL: " << minL << endl;
                setmax(d[j], d[i] + minL);
            }
        }
        /*         
        repeat(i, N) cout << perm[i] << " -> ";
        cout << endl;
        cout << "d: ";
        repeat(i, N) cout << d[i] << " ";
        cout << endl; 
        */
        setmin(res, d[N - 1]);
    } while (next_permutation(begin(perm), end(perm)));

    cout << res << endl;
    return 0;
}