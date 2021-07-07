#include <bits/stdc++.h>
using namespace std;

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
