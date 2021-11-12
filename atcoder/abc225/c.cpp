#include <bits/stdc++.h>
using namespace std;
int mat[10010][7];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> mat[i][j];
    }
  }

  bool flg = true;
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      flg &= ((mat[i][j] - mat[i - 1][j]) == 7);
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      flg &= ((mat[i][j] - mat[i][j - 1]) == 1);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m - 1; ++j) {
      flg &= (mat[i][j] % 7 != 0);
    }
  }

  cout << (flg ? "Yes" : "No") << endl;
}