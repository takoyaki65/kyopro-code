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

template <long long MOD, long long base>
struct rolling_hash {
  int n;
  vector<long long> hs, pw;
  map<long long, long long> Map;
  rolling_hash(const string& s) {
    n = s.size();
    hs.assign(n + 1, 0);
    pw.assign(n + 1, 0);
    hs[0] = 0;
    pw[0] = 1;
    for (int i = 0; i < n; ++i) {
      pw[i + 1] = pw[i] * base % MOD;
      hs[i + 1] = (hs[i] * base + s[i]) % MOD;
    }
  }

  // 区間[l, r)の部分文字列のハッシュを取る
  long long hash(int l, int r) {
    return ((hs[r] - hs[l] * pw[r - l] % MOD + MOD) % MOD);
  }
};

// https://gist.github.com/privet-kitty/295ac9202b7abb3039b493f8238bf40f#file-modulus-random-base-pair64-txt
// から、2^32以下の素数をmodとし、その原子根をbaseとするのがいいらしい？
// 参考: https://competitive12.blogspot.com/2019/06/blog-post_26.html
// ただ、
// mod = 4294967291
// base = 2095716802
// でやったらハッシュが衝突してしまった。。。
const long long mod = 1000000007LL;
const long long base = 9973;
using rolHash = rolling_hash<mod, base>;

const char rgb[] = "RGB";

int main() {
  int N;
  string S, T;
  cin >> N >> S >> T;
  int ans = 0;
  rolHash hash_T(T);
  for (int i = 0; i < 3; ++i) {
    char ch1 = rgb[i], ch2 = rgb[(i + 1) % 3];
    for (int j = 0; j < N; ++j) {
      if (S[j] == ch1)
        S[j] = ch2;
      else if (S[j] == ch2)
        S[j] = ch1;
    }

    // ローリングハッシュ作成
    rolHash hash_S(S);

    // 部分文字列の等号を調べる
    for (int k = 1; k < N; ++k) {
      int len = N - k;
      // if (S.substr(k, len) == T.substr(0, len)) {
      //   long long hS = hash_S.hash(k, k + len);
      //   long long hT = hash_T.hash(0, len);
      //   if (hS != hT) {
      //     cout << "error:" << endl;
      //     cout << S.substr(k, len) << " : " << hS << endl;
      //     cout << T.substr(0, len) << " : " << hT << endl;
      //   }
      // }
      if (hash_S.hash(k, k + len) == hash_T.hash(0, len))
        ans += 1;

      // if (S.substr(0, len) == T.substr(k, len)) {
      //   long long hS = hash_S.hash(0, len);
      //   long long hT = hash_T.hash(k, k + len);
      //   if (hS != hT) {
      //     cout << "error:" << endl;
      //     cout << S.substr(0, len) << " : " << hS << endl;
      //     cout << T.substr(k, len) << " : " << hT << endl;
      //   }
      // }
      if (hash_S.hash(0, len) == hash_T.hash(k, k + len))
        ans += 1;
    }

    if (hash_S.hash(0, N) == hash_T.hash(0, N))
      ans += 1;

    // 元に戻す
    for (int j = 0; j < N; ++j) {
      if (S[j] == ch1)
        S[j] = ch2;
      else if (S[j] == ch2)
        S[j] = ch1;
    }
  }

  cout << ans << endl;
  return 0;
}