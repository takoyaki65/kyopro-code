#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Z-algorithm
 *
 * @ref snuke https://snuke.hatenablog.com/entry/2014/12/03/214243
 *
 * @param S 文字列
 * @param Z Z-array Z[i] = len: Z[0:len)とZ[i:i+len)が一致する
 */
void Zarray(const string& S, vector<int>& Z) {
  const int n = S.size();
  if (Z.size() != n)
    Z.assign(n, 0);
  Z[0] = n;
  // i := 現在見ている文字の先頭
  // j := 共通接頭辞の長さ
  int i = 1, j = 0;
  while (i < n) {
    while (i + j < n && S[j] == S[i + j])
      j += 1;
    Z[i] = j;
    if (j == 0) {
      i += 1;
      continue;
    }
    int k = 1;
    while (i + k < n && k + Z[k] < j)
      Z[i + k] = Z[k], k += 1;
    i += k;
    j -= k;
  }
}
