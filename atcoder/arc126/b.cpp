#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> seq(m);
  {
    vector<pair<int, int>> a(m);
    for (int i = 0; i < m; i++) {
      cin >> a[i].first >> a[i].second;
    }
    // sort by a[i].first in ascending order
    // if a[i].first and a[j].first are tied, sort by a[i].second in descending
    // order
    sort(a.begin(), a.end(),
         [](const pair<int, int>& x, const pair<int, int>& y) {
           if (x.first == y.first) {
             return x.second > y.second;
           }
           return x.first < y.first;
         });
    // store a[i].second to seq
    for (int i = 0; i < m; i++) {
      seq[i] = a[i].second;
    }
  }

  // compute the Largest Increasing Subsequence (LIS) of seq
  // with dynamic programming and binary search
  // d[l] := the minimum value of the last element of the Increasing Subsequence
  // whose length is l.
  // initially, d[0] = -inf, d[l] = +inf for l > 0
  vector<int> d;
  for (const int& x: seq) {
    auto it = lower_bound(d.begin(), d.end(), x);
    if (it == d.end()) {
      d.push_back(x);
    } else {
      *it = x;
    }
  }

  cout << d.size() << endl;
  return 0;
}