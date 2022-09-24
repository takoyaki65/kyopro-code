#include <iostream>
using namespace std;
char grid[1010][1010];
int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i)
    cin >> grid[i];

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      if (!(grid[i][j] == 'W' && grid[j][i] == 'L') &&
          !(grid[i][j] == 'L' && grid[j][i] == 'W') &&
          !(grid[i][j] == 'D' && grid[j][i] == 'D')) {
        cout << "incorrect" << endl;
        return 0;
      }
    }
  }

  cout << "correct" << endl;
  return 0;
}