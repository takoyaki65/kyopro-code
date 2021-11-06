#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); ++i)
using ll = long long;

int main() {
  vector<string> s(3);
  rep(i, 3) cin >> s[i];
  map<char, ll> mp;
  set<char> heads;
  rep(i, 3) {
    reverse(s[i].begin(), s[i].end());
    ll co = 1;
    if (i == 2)
      co = -1;
    for (char c : s[i]) {
      mp[c] += co;
      co *= 10;
    }
    reverse(s[i].begin(), s[i].end());
    heads.insert(s[i][0]);
  }

  if (mp.size() > 10) {
    cout << "UNSOLVABLE" << endl;
    return 0;
  }

  vector<int> p(10);
  iota(p.begin(), p.end(), 0);
  do {
    int i = 0;
    ll tot = 0;
    for (auto x : mp) {
      char c = x.first;
      ll co = x.second;
      if (p[i] == 0 && heads.count(c))
        tot = 1e18;
      tot += co * p[i];
      ++i;
    }
    if (tot == 0) {
      i = 0;
      for (auto& x : mp) {
        x.second = p[i];
        ++i;
      }
      rep(i, 3) {
        ll x = 0;
        for (char c : s[i]) {
          x = x * 10 + mp[c];
        }
        cout << x << endl;
      }
      return 0;
    }
  } while (next_permutation(p.begin(), p.end()));
  cout << "UNSOLVABLE" << endl;
  return 0;
}