#include <iostream>
#include <queue>
#include <utility>
using namespace std;
bool grid[2100][2100];
const int dx[6] = {-1, -1, 0, 0, 1, 1};
const int dy[6] = {-1, 0, -1, +1, 0, +1};
void bfs(int sx, int sy) {
  queue<pair<int, int>> que;
  que.push({sx, sy});
  while (!que.empty()) {
    auto [x, y] = que.front();
    que.pop();
    if (!grid[x][y])
      continue;
    grid[x][y] = false;
    for (int k = 0; k < 6; ++k) {
      const int nx = x + dx[k], ny = y + dy[k];
      if (nx < 0 || nx >= 2100 || ny < 0 || ny >= 2100)
        continue;
      if (grid[nx][ny]) {
        que.push({nx, ny});
      }
    }
  }
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    x += 1000, y += 1000;
    grid[x][y] = true;
  }

  int ans = 0;
  for (int i = 0; i < 2100; ++i) {
    for (int j = 0; j < 2100; ++j) {
      if (grid[i][j]) {
        bfs(i, j);
        ans += 1;
      }
    }
  }
  cout << ans << endl;
  return 0;
}