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

using pii = pair<int, int>;
const int INF = 1e9;

int main() {
    int R, C, K, N;
    cin >> R >> C >> K >> N;

    set<pii> rc;
    vector<pii> Rs(R, make_pair(0, 0)), Cs(C, make_pair(0, 0));
    repeat(i, N) {
        int r, c;
        cin >> r >> c;
        --r, --c;
        rc.emplace(r, c);
        ++Rs[r].first;
        ++Cs[c].first;
    }

    repeat(i, R) {
        Rs[i].second = i;
    }
    repeat(i, C) {
        Cs[i].second = i;
    }
    sort(Rs.begin(), Rs.end());
    sort(Cs.begin(), Cs.end());

    long long res = 0;
    repeat(i, N) {
        int p = Rs[i].first;
        int x = Rs[i].second;
        auto itr = lower_bound(Cs.begin(), Cs.end(), make_pair(K - p, -1));
        auto end_itr = upper_bound(Cs.begin(), Cs.end(), make_pair(K - p + 1, INF));
        while (itr != end_itr) {
            int y = itr->second;
            int q = itr->first;
            int b = rc.find({x, y}) != rc.end();
            //cout << "x: " << x << " y: " << y << " b: " << b << endl;
            if (p + q - b == K) ++res;
            ++itr;
        }
    }
    cout << res << endl;
    return 0;
}