#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

bool comp(const pi& l, const pi& r) {
  double atl = atan2((double)l.second, (double)l.first);
  double atr = atan2((double)r.second, (double)r.first);
  return (atl != atr) ? (atl < atr)
                      : ((l.first * l.first + l.second * l.second) <
                         (r.first * r.first + r.second * r.second));
}

void z_algorithm(vector<int>& s, vector<int>& arr) {
  int i, j, k, l;
  l = s.size();
  arr[0] = l;
  i = 1;
  j = 0;
  while (i < l) {
    while ((i + j) < l) {
      if (s[j] != s[i + j]) {
        break;
      }
      j++;
    }
    arr[i] = j;
    if (j == 0) {
      i++;
      continue;
    }
    k = 1;
    while ((i + k) < l) {
      if (k + arr[k] >= arr[i]) {
        break;
      }
      arr[i + k] = arr[k];
      k++;
    }
    j = arr[i] - k;
    i += k;
  }
}

vector<int> pts_to_str(vector<pi> pts) {
  vector<int> res;
  int gx = 0, gy = 0;
  for (auto& nx : pts) {
    gx += nx.first;
    gy += nx.second;
  }
  gx /= ((int)pts.size());
  gy /= ((int)pts.size());
  vector<pi> vcs;
  for (auto& nx : pts) {
    int vx = nx.first - gx;
    int vy = nx.second - gy;
    if (vx == 0 && vy == 0) {
      continue;
    }
    vcs.push_back({vx, vy});
  }
  sort(vcs.begin(), vcs.end(), comp);
  int sz = vcs.size();
  // for (int i = 0; i < sz; ++i) {
  //   cout << "(" << vcs[i].first << ", " << vcs[i].second << ")" << endl;
  // }
  // cout << endl;
  for (int i = 0; i < sz; i++) {
    res.push_back(vcs[i].first * vcs[i].first + vcs[i].second * vcs[i].second);
    res.push_back(vcs[i].first * vcs[(i + 1) % sz].first +
                  vcs[i].second * vcs[(i + 1) % sz].second);
    res.push_back(vcs[i].first * vcs[(i + 1) % sz].second -
                  vcs[i].second * vcs[(i + 1) % sz].first);
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  if (n == 1) {
    cout << "Yes\n";
    return 0;
  }
  vector<pi> a(n), b(n);
  for (auto& nx : a) {
    cin >> nx.first >> nx.second;
    nx.first *= n;
    nx.second *= n;
  }
  for (auto& nx : b) {
    cin >> nx.first >> nx.second;
    nx.first *= n;
    nx.second *= n;
  }
  vector<int> as = pts_to_str(a);
  vector<int> bs = pts_to_str(b);
  if (as.size() != bs.size()) {
    cout << "No\n";
    return 0;
  }
  int sz = as.size();
  vector<int> zs;
  zs.insert(zs.end(), as.begin(), as.end());
  zs.insert(zs.end(), bs.begin(), bs.end());
  zs.insert(zs.end(), bs.begin(), bs.end());
  vector<int> zr(sz * 3);
  z_algorithm(zs, zr);
  for (int j = sz; j < 2 * sz; j += 3) {
    if (zr[j] >= sz) {
      cout << "Yes\n";
      return 0;
    }
  }
  cout << "No\n";
  return 0;
}