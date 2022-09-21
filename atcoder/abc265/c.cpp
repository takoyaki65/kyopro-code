#include <iostream>
using namespace std;
char g[510][510];
bool visited[510][510];
int main() {
  int h, w;
  cin >> h >> w;
  for (int i = 0; i < h; ++i)
    cin >> g[i];
  int x = 0, y = 0;
  int nx, ny;
  while (true) {
    if (visited[x][y]) {
      cout << -1 << endl;
      return 0;
    }
    visited[x][y] = true;
    switch (g[x][y]) {
      case 'U':
        nx = x - 1, ny = y;
        break;
      case 'D':
        nx = x + 1, ny = y;
        break;
      case 'L':
        nx = x, ny = y - 1;
        break;
      case 'R':
        nx = x, ny = y + 1;
        break;
      default:
        break;
    }
    if (nx < 0 || nx >= h || ny < 0 || ny >= w) {
      break;
    }
    x = nx, y = ny;
  }

  cout << x + 1 << " " << y + 1 << endl;
  return 0;
}