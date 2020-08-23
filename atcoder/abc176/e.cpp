#include <algorithm>
#include <iostream>
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

// 座標圧縮しか思いつかない
// 爆弾の数が3×10^5だから、座標圧縮かな
// でも、爆弾が斜めにきれいに並んでいたら、座標圧縮しても意味ないじゃん。
// 行と列個別に「最も爆破できるケースを求めて」、それらをA,Bとして、
// (A,B)に爆破対称があるなら、max(R) + max(C) - 1, ないならmax(R) + max(C)

int main() {
    int H, W, M;
    cin >> H >> W >> M;
    set<int> X, Y;
    set<pair<int, int>> hw;
    vector<int> Xb(H, 0), Yb(W, 0);
    repeat(i, M) {
        int h, w;
        cin >> h >> w;
        --h, --w;
        hw.emplace(h, w);
        X.insert(h);
        Y.insert(w);
        ++Xb[h];
        ++Yb[w];
    }
    /* 
    cout << "Xb: " << endl;
    repeat(i, H) cout << Xb[i] << " ";
    cout << endl;
    cout << "Yb: " << endl;
    repeat(i, W) cout << Yb[i] << " ";
    cout << endl;
 */
    int R = -1, C = -1;
    for (int x : X) {
        setmax(R, Xb[x]);
    }
    for (int y : Y) {
        setmax(C, Yb[y]);
    }
    vector<int> Rx, Cy;
    for (int x : X) {
        if (R == Xb[x]) Rx.push_back(x);
    }
    for (int y : Y) {
        if (C == Yb[y]) Cy.push_back(y);
    }
    for (int x : Rx) {
        for (int y : Cy) {
            if (!hw.count(make_pair(x, y))) {
                cout << R + C << endl;
                return 0;
            }
        }
    }
    cout << R + C - 1 << endl;
    return 0;
}