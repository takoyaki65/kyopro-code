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

int N, M, Q;
vector<int> In[100005];
int A[100005], B[100005];
long long dp[100005];

int main() {
  cin >> N >> M >> Q;
  repeat(i, M) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    In[y].push_back(x);
  }
  repeat(i, Q) {
    cin >> A[i] >> B[i];
    --A[i], --B[i];
  }

  for (int i = 0; i * 64 < Q; ++i) {
    memset(dp, 0, N * sizeof(long long));
    int left = i * 64;
    int right = min((i + 1) * 64, Q);
    // cout << "left: " << left << " right: " << right << endl;
    for (int j = left; j < right; ++j) {
      dp[A[j]] |= 1LL << (j - left);
    }
    for (int j = 0; j < N; ++j) {
      for (const int& from : In[j]) {
        dp[j] |= dp[from];
      }
    }
    for (int j = left; j < right; ++j) {
      if ((dp[B[j]] >> (j - left)) & 1) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    }
  }

  return 0;
}