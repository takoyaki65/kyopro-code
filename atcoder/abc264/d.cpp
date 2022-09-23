#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

int dp[5100];
string i2s[5100];
unordered_map<string, int> s2i;
int main() {
  {
    string p = "atcoder";
    sort(p.begin(), p.end());
    int i = 0;
    do {
      i2s[i++] = p;
    } while (next_permutation(p.begin(), p.end()));
    for (int k = 0; k < i; ++k) {
      s2i[i2s[k]] = k;
    }
  }

  string s;
  cin >> s;
  queue<pair<int, int>> que;
  memset(dp, -1, sizeof(dp));
  que.push({s2i[s], 0});
  while (!que.empty()) {
    auto [idx, x] = que.front();
    que.pop();
    if (dp[idx] != -1)
      continue;
    dp[idx] = x;
    string ps = i2s[idx];
    if (ps == "atcoder")
      break;
    for (int i = 0; i < 6; ++i) {
      swap(ps[i], ps[i + 1]);
      int nidx = s2i[ps];
      if (dp[nidx] == -1)
        que.push({nidx, x + 1});
      swap(ps[i], ps[i + 1]);
    }
  }

  int ans = dp[s2i["atcoder"]];
  cout << ans << endl;
  return 0;
}