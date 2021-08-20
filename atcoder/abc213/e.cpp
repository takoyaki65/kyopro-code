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

int h, w;
char S[510][510];

char available[5][6] = {".***.", "*****", "**T**", "*****", ".***."};
const int cx = 2, cy = 2;
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

struct State {
  int x, y, d;
};

int dist[510][510];

int main() {
  cin >> h >> w;
  repeat(i, h) cin >> S[i];

  memset(dist, -1, sizeof(dist));
  deque<State> deq;
  deq.push_back({0, 0, 0});
  while (!deq.empty()) {
    auto [x, y, d] = deq.front();
    deq.pop_front();
    if (dist[x][y] != -1)
      continue;
    dist[x][y] = d;
    // コスト0移動
    repeat(k, 4) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= h || ny < 0 || ny >= w)
        continue;
      if (S[nx][ny] == '#')
        continue;
      deq.push_front({nx, ny, d});
    }
    // コスト1移動
    for (int i = -2; i <= 2; ++i) {
      for (int j = -2; j <= 2; ++j) {
        if (available[cx + i][cy + j] == 'T' ||
            available[cx + i][cy + j] == '.')
          continue;
        int nx = x + i, ny = y + j;
        if (nx < 0 || nx >= h || ny < 0 || ny >= w)
          continue;
        deq.push_back({nx, ny, d + 1});
      }
    }
  }

  cout << dist[h - 1][w - 1] << endl;

  return 0;
}