#include <bits/stdc++.h>
using namespace std;

int n;
int a[17][17];
bool used[17];
int arr[17];

int bfs(int count) {
  if (count == n) {
    int val = 0;
    for (int i = 0; i < n; i += 2)
      val ^= a[arr[i]][arr[i + 1]];
    return val;
  }

  int ret = 0;
  int i = 0;
  while (used[i])
    i += 1;
  for (int j = i + 1; j < n; ++j)
    if (!used[j]) {
      used[i] = used[j] = true;
      arr[count] = i, arr[count + 1] = j;
      ret = max(ret, bfs(count + 2));
      used[i] = used[j] = false;
    }

  return ret;
}

int main() {
  cin >> n;
  n *= 2;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = i + 1; j < n; ++j) {
      cin >> a[i][j];
      a[j][i] = a[i][j];
    }
  }

  cout << bfs(0) << endl;
  return 0;
}