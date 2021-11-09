#include <bits/stdc++.h>
using namespace std;

vector<int> graph[200010];
int T[200010];
int K[200010];
bool used[200010];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> T[i];
    cin >> K[i];
    for (int j = 0; j < K[i]; ++j) {
      int v;
      cin >> v;
      graph[i].push_back(v - 1);
    }
  }

  used[n - 1] = true;
  for (int i = n - 1; i >= 0; --i) {
    if (used[i]) {
      for (int j = 0; j < K[i]; ++j) {
        used[graph[i][j]] = true;
      }
    }
  }

  long long res = 0;
  for (int i = 0; i < n; ++i) {
    if (used[i])
      res += T[i];
  }
  cout << res << endl;
  return 0;
}