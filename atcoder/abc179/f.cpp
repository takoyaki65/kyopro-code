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

struct area {
    bool x_div;
    int knife;
    int left, right;
    int lx, ly, rx, ry;
    area(bool div, int knife_, int left_, int right_, int lx_, int ly_, int rx_, int ry_) : x_div(div), knife(knife_), left(left_), right(right_), lx(lx_), ly(ly_), rx(rx_), ry(ry_) {}
};

class areadiv {
    vector<area> tree;

   public:
    areadiv(int N) {}
    //tree.push_back(area(false, -1, -1, -1, 1, 1, N - 2, N - 2)):
    int xdiv(int x) {
    }

    int ydiv(int y) {
    }
};

int main() {
    return 0;
}