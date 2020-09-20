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

// セグ木が使えるじゃん！
// セグ木だけじゃだめらしい、どうすれば、、、

template <typename T>
struct BIT {
   private:
    vector<T> array;
    const int n;

   public:
    BIT(int _n) : array(_n + 1, 0), n(_n) {}
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += array[i];
            i -= i & -i;
        }
        return s;
    }

    // [i, j]
    T sum(int i, int j) {
        T ret_i = sum(i - 1);
        T ret_j = sum(j);
        return ret_j - ret_i;
    }

    // i番目に要素xを追加
    void add(int i, T x) {
        while (i <= n) {
            array[i] += x;
            i += i & -i;
        }
    }
};

int main() {
    int N;
    cin >> N;
    vector<pair<int, int>> xy(N);
    repeat(i, N) {
        cin >> xy[i].first >> xy[i].second;
        xy[i].first, xy[i].second;
    }
    sort(xy.begin(), xy.end());
    BIT<int> ypre(N), ypas(N);
    repeat(i, N) {
        ypre.add(xy[i].second, 1);
        //cout << "i add" << i << endl;
    }

    repeat(k, N) {
        int res = ypre.sum(xy[k].second, N) + ypas.sum(1, xy[k].second);
        cout << res << endl;
        ypre.add(xy[k].second, -1);
        ypas.add(xy[k].second, 1);
    }
    return 0;
}