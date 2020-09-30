#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
#define sz(x) int(x.size())
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

// 二人がすべての料理を一個ずつ食べられるとする
// スコアの差はsum(Ai) - sum(Bi)
// そこから、各ターンで片方しか食べない料理を1つずつ決める
// 高橋が料理iを選ぶとスコアの差はBi広がる
// 青木が料理iを選ぶとスコアの差はAi縮まる

//#define NDEBUG
// なぜか半分waになる、、、

int main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    vector<pair<int, int>> ai(n), bi(n);
    long long ans = 0;
    repeat(i, n) {
        cin >> a[i] >> b[i];
        ai[i].first = a[i], bi[i].first = b[i];
        ai[i].second = i, bi[i].second = i;
        ans += a[i] - b[i];
    }
    sort(ai.rbegin(), ai.rend());
    sort(bi.rbegin(), bi.rend());

    int turn = 0;
    int tkhs = 0, aok = 0;
    vector<bool> used(n);
    while (turn++ < n) {
        //cout << "turn: " << turn << endl;
        if (turn % 2) {
            while (used[bi[tkhs].second]) {
                ++tkhs;
                assert(tkhs < n);
            }
            //cout << "tkhs: " << tkhs << endl;
            used[bi[tkhs].second] = true;
            ans += b[bi[tkhs].second];
        } else {
            while (used[ai[aok].second]) {
                ++aok;
                assert(aok < n);
            }
            //cout << "aok: " << aok << endl;
            used[ai[aok].second] = true;
            ans -= a[ai[aok].second];
        }
    }

    cout << ans << endl;

    return 0;
}
