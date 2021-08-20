#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
#define bit_stand(n, k) ((n >> k) & 1)
using namespace std;

template <class T>
inline int sz(T& x) {
  return x.size();
}

template <class T>
inline bool setmax(T& a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T& a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}

template <typename T, typename X>
auto vectors(T a, X x) {
  return vector<T>(x, a);
}

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
  auto cont = vectors(a, y, zs...);
  return vector<decltype(cont)>(x, cont);
}

int h, w, n;
int cx[100005], cy[100005];
int tx[100005], ty[100005];

int main() {
  cin >> h >> w >> n;
  repeat(i, n) cin >> cx[i] >> cy[i];
  repeat(i, n) tx[i] = cx[i], ty[i] = cy[i];
  sort(tx, tx + n);
  sort(ty, ty + n);
  int end_x = unique(tx, tx + n) - tx;
  int end_y = unique(ty, ty + n) - ty;

  map<int, int> px, py;
  repeat(i, end_x) px[tx[i]] = i + 1;
  repeat(i, end_y) py[ty[i]] = i + 1;

  repeat(i, n) { cout << px[cx[i]] << " " << py[cy[i]] << endl; }

  return 0;
}