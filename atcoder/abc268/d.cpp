#include <bits/stdc++.h>
using namespace std;

int n, m;
set<string> dict;
string sv[10];
int perm[10];
int bar_num[10];

string gen_username() {
  string res = "";
  for (int i = 0; i < n - 1; ++i) {
    res += sv[perm[i]];
    res += string(bar_num[i], '_');
  }
  res += sv[perm[n - 1]];
  return res;
}

bool dfs(int idx, int remain) {
  if (idx >= n - 1) {
    // for (int i = 0; i < n - 1; ++i) {
    //   assert(bar_num[i] >= 1);
    // }
    string res = gen_username();
    if (res.size() >= 3 && res.size() <= 16 && dict.count(res) == 0) {
      cout << res << endl;
      return true;
    }
  }

  for (int i = 1; i <= remain; ++i) {
    bar_num[idx] = i;
    if (dfs(idx + 1, remain - i))
      return true;
  }

  return false;
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> sv[i];
  }
  for (int i = 0; i < m; ++i) {
    string tmp;
    cin >> tmp;
    dict.insert(tmp);
  }

  int u_max = 16;
  for (int i = 0; i < n; ++i)
    u_max -= sv[i].size();

  // cout << "u_max: " << u_max << endl;

  iota(perm, perm + n, 0);
  do {
    if (dfs(0, u_max)) {
      return 0;
    }
  } while (next_permutation(perm, perm + n));

  cout << -1 << endl;
  return 0;
}