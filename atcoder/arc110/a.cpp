#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll lcm(ll a, ll b) { return a * b / __gcd(a, b); }

ll lcm(const vector<ll> &vec) {
  if (vec.empty()) return 0;
  ll ret = 1;
  for (const ll &x : vec) {
    ret = lcm(ret, x);
  }
  return ret;
}

int main() {
  ll n{0};
  cin >> n;
  vector<ll> vec(n - 1);
  iota(vec.begin(), vec.end(), 2);
  cout << lcm(vec) + 1 << endl;
  return 0;
}