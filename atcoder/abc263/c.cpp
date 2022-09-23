#include <iostream>
using namespace std;
int n, m;
int arr[20];
void dfs(int idx, int prev) {
  if (idx == n) {
    for (int i = 0; i < n; ++i) {
      cout << arr[i] << (i == n - 1 ? "\n" : " ");
    }
    return;
  }

  for (int i = prev + 1; i <= m; ++i) {
    arr[idx] = i;
    dfs(idx + 1, i);
  }
}
int main() {
  cin >> n >> m;
  dfs(0, 0);
  return 0;
}
