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
#include <set>
#include <stack>
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

// Lidx[ch][idx] :=
// 文字列の[idx,N)の区間でch番目のアルファベットが
// 最も左にあるときのインデックス   無い場合は-1
int Lidx[28][100010];

int main() {
  int N, K;
  string S;
  cin >> N >> K >> S;
  memset(Lidx, -1, sizeof(Lidx));

  for (int i = N - 1; i >= 0; i--) {
    if (i + 1 < N) {
      repeat(j, 'z' - 'a' + 1) Lidx[j][i] = Lidx[j][i + 1];
    }

    Lidx[S[i] - 'a'][i] = i;
  }

  int substr_size = 0;
  string ans(K, 'z');
  int idx = 0;
  while (idx < N && substr_size < K) {
    // [idx, N)以降で最も左にあるアルファベットのインデックスを見る
    repeat(i, 'z' - 'a' + 1) {
      if (Lidx[i][idx] == -1)
        continue;
      // その文字を取った後の、それ以降の文字Sの長さと残り必要な部分文字列の長さ
      int remain_s_length = N - Lidx[i][idx] - 1;
      int remain_substr = K - substr_size - 1;
      if (remain_s_length >= remain_substr) {
        ans[substr_size++] = char(i + 'a');
        idx = Lidx[i][idx] + 1;
        break;
      }
    }
  }
  cout << ans << endl;

  return 0;
}