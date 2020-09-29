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

const int MAX_RATE = 100010;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> rh(n);
    repeat(i, n) {
        cin >> rh[i].first >> rh[i].second;
        rh[i].second--;
    }
    vector<int> hist(MAX_RATE + 1);
    repeat(i, n) {
        hist[rh[i].first]++;
    }
    vector<int> acum(MAX_RATE + 1);
    repeat(i, MAX_RATE) {
        acum[i + 1] = acum[i] + hist[i];
    }
    auto hand = vectors(0, MAX_RATE + 1, 3);
    repeat(i, n) {
        hand[rh[i].first][rh[i].second]++;
    }

    repeat(i, n) {
        int win = 0, lose = 0, draw = 0;
        int r = rh[i].first;
        int h = rh[i].second;
        win = acum[r];
        lose = acum[MAX_RATE] - acum[r + 1];
        draw = hand[r][h];
        win += hand[r][(h + 1) % 3];
        lose += hand[r][(h - 1 + 3) % 3];
        draw--;
        //assert(win + lose + draw == n - 1);
        cout << win << " " << lose << " " << draw << endl;
    }
    return 0;
}