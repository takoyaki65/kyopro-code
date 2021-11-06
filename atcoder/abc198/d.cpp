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

bool exist[30];
int num[30];

int s1d[12], s2d[12], s3d[12];

int main() {
  string s1, s2, s3;
  cin >> s1 >> s2 >> s3;
  for (char ch : s1)
    exist[ch - 'a'] = true;
  for (char ch : s2)
    exist[ch - 'a'] = true;
  for (char ch : s3)
    exist[ch - 'a'] = true;
  int cnt = 0;
  repeat(i, 'z' - 'a' + 1) num[i] = -1;
  repeat(i, 'z' - 'a' + 1) if (exist[i]) { num[i] = 1; }
  repeat(i, 'z' - 'a' + 1) if (num[i] == 1) { num[i] = cnt++; }
  if (cnt > 10) {
    cout << "UNSOLVABLE" << endl;
    return 0;
  }

  vector<int> perm(10);
  iota(perm.begin(), perm.end(), 0);

  do {
    memset(s1d, 0, sizeof(s1d));
    memset(s2d, 0, sizeof(s2d));
    memset(s3d, 0, sizeof(s3d));
    for (int i = 0; i < s1.size(); ++i) {
      s1d[i] = perm[num[s1[i] - 'a']];
    }
    for (int i = 0; i < s2.size(); ++i) {
      s2d[i] = perm[num[s2[i] - 'a']];
    }
    for (int i = 0; i < s3.size(); ++i) {
      s3d[i] = perm[num[s3[i] - 'a']];
    }
    if (s1d[0] == 0 || s2d[0] == 0 || s3d[0] == 0)
      continue;
    long long a = 0, b = 0, c = 0;
    for (int i = 0; i < s1.size(); ++i) {
      a *= 10LL;
      a += s1d[i];
    }
    for (int i = 0; i < s2.size(); ++i) {
      b *= 10LL;
      b += s2d[i];
    }
    for (int i = 0; i < s3.size(); ++i) {
      c *= 10LL;
      c += s3d[i];
    }

    if (a + b == c) {
      string as, bs, cs;
      for (int i = 0; i < s1.size(); ++i)
        as.push_back(s1d[i] + '0');
      for (int i = 0; i < s2.size(); ++i)
        bs.push_back(s2d[i] + '0');
      for (int i = 0; i < s3.size(); ++i)
        cs.push_back(s3d[i] + '0');
      cout << as << endl << bs << endl << cs << endl;
      return 0;
    }
  } while (next_permutation(perm.begin(), perm.end()));

  cout << "UNSOLVABLE" << endl;
  return 0;
}