#include <bit>
#include <cassert>
#include <iostream>
using namespace std;
int a[12][12], b[12][12];
int h1, h2, w1, w2;
int pop_count(int s) {
  int ret = 0;
  while (s > 0) {
    ret += (s & 1);
    s >>= 1;
  }
  return ret;
}

void display(int row, int col) {
  int ai = 0, bi = 0;
  while (bi < h2) {
    while ((row & (1 << ai)) == 0)
      ai += 1;
    int aj = 0, bj = 0;
    while (bj < w2) {
      while ((col & (1 << aj)) == 0)
        aj += 1;
      cout << a[ai][aj] << " ";
      bj += 1;
      aj += 1;
    }
    bi += 1;
    ai += 1;
    cout << endl;
  }
}

bool check(int row, int col) {
  int ai = 0, bi = 0;
  while (bi < h2) {
    while ((row & (1 << ai)) == 0)
      ai += 1;
    int aj = 0, bj = 0;
    while (bj < w2) {
      while ((col & (1 << aj)) == 0)
        aj += 1;
      if (a[ai][aj] != b[bi][bj])
        return false;
      bj += 1;
      aj += 1;
    }
    bi += 1;
    ai += 1;
  }
  return true;
}

int main() {
  // for (int i = 0; i < 10000; ++i) {
  //   assert(pop_count(i) == __popcount(i));
  // }
  cin >> h1 >> w1;
  for (int i = 0; i < h1; ++i)
    for (int j = 0; j < w1; ++j)
      cin >> a[i][j];
  cin >> h2 >> w2;
  for (int i = 0; i < h2; ++i)
    for (int j = 0; j < w2; ++j)
      cin >> b[i][j];

  for (int row = 1; row < (1 << h1); ++row) {
    if (pop_count(row) != h2)
      continue;
    for (int col = 1; col < (1 << w1); ++col) {
      if (pop_count(col) != w2)
        continue;
      // cout << "row: " << row << "col: " << col << endl;
      // display(row, col);
      if (check(row, col)) {
        cout << "Yes" << endl;
        return 0;
      }
    }
  }
  cout << "No" << endl;
  return 0;
}