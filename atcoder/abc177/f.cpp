#include <algorithm>
#include <cmath>
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

const int MAX_AI = 1000010;
#define PRINT(X) cout << #X << " : " << X << endl

// dpのはずなんだけど、計算量がO(HW)だと無理そう、、、
// あとで解く
// あとで遅延セグ木で解く

int main() {
    int H, W;
    cin >> H >> W;

    set<pair<int, int>> se;  // first := 今の地点 second := 開始地点
    multiset<int> dist;

    repeat(i, W) {
        se.emplace(i, i);
        dist.insert(0);
    }

    repeat(i, H) {
        int A, B;
        cin >> A >> B;
        --A;  // [A, B) 0-indexed
        auto itr = se.lower_bound(make_pair(A, -1));
        int max_r = -1;
        while (itr != se.end() && itr->first < B) {
            setmax(max_r, itr->second);
            dist.erase(dist.find(itr->first - itr->second));
            // https://ox8000ffff.hatenadiary.org/entry/20100225/1267201650
            se.erase(itr++);
        }
        if (max_r != -1 && B < W) {
            se.emplace(B, max_r);
            dist.insert(B - max_r);
        }
        if (!dist.empty()) {
            cout << (*dist.begin()) + i + 1 << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}