#include <algorithm>
#include <array>
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

int N;
const int MAX_V = 52 * 52 * 52;
vector<int> G[MAX_V + 10];
vector<int> rG[MAX_V + 10];

int ch2dig(char ch) {
  if ('a' <= ch && ch <= 'z')
    return ch - 'a';
  else if ('A' <= ch && ch <= 'Z')
    return ch - 'A' + 26;
  return 0;
}

int Hash(char ch1, char ch2, char ch3) {
  return ch2dig(ch1) + ch2dig(ch2) * 52 + ch2dig(ch3) * 52 * 52;
}

int dp[MAX_V + 10];
bool visit[MAX_V + 10];
int Q[200005];

int rec(int cur) {
  visit[cur] = true;
  if (G[cur].size() == 0)
    return dp[cur] = 0;
  int ret = -1;
  for (const int& to : G[cur]) {
    if (visit[to] == false) {
      int val = rec(to);
      if (val != -1)
        ret = max(ret, 1 + val);
    } else {
      // visit[to] == true
      if (dp[to] == -1) {
        // do nothing
      } else {
        ret = max(ret, 1 + dp[to]);
      }
    }
  }
  return dp[cur] = ret;
}

int main() {
  int N;
  cin >> N;
  string S;
  repeat(i, N) {
    cin >> S;
    const int n = S.size();
    int a = Hash(S[0], S[1], S[2]);
    int b = Hash(S[n - 3], S[n - 2], S[n - 1]);
    // a -> b
    G[a].push_back(b);
    rG[b].push_back(a);
    Q[i] = b;
  }

  memset(dp, -1, sizeof(dp));
  memset(visit, false, sizeof(visit));
  queue<int> que;
  repeat(i, MAX_V) {
    if (G[i].size() == 0) {
      // 負け
      dp[i] = 0;
      for (const int& to : rG[i]) {
        que.push(to);
      }
    }
  }

  while (!que.empty()) {
    int v = que.front();
    que.pop();
    if (dp[v] != -1)
      continue;
    int ne = G[v].size();
    int winV = 0, loseV = 0;
    for (const int& to : G[v]) {
      if (dp[to] == 0)
        loseV += 1;
      else if (dp[to] == 1)
        winV += 1;
    }
    // 1つでも負けの頂点につながっていれば勝ち
    // 全て勝ちの頂点だったら負け
    // そうでなかったら未確定
    if (loseV > 0) {
      dp[v] = 1;
    } else if (winV == ne) {
      dp[v] = 0;
    }

    if (dp[v] != -1) {
      for (const int& to : rG[v]) {
        if (dp[to] == -1)
          que.push(to);
      }
    }
  }

  repeat(i, N) {
    int val = dp[Q[i]];
    if (val == -1) {
      cout << "Draw" << endl;
    } else if (val == 1) {
      cout << "Aoki" << endl;
    } else {
      cout << "Takahashi" << endl;
    }
  }

  return 0;
}