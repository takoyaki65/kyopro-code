#include <iostream>
using namespace std;
#define MAXT 20
int main() {
  int n;
  cin >> n;
  int qc = 0;
  int x, y;
  int a = 1, b = n;
  while (b - a >= 1) {
    int m = a + (b - a) / 2;
    cout << "? " << a << " " << m << " " << 1 << " " << n << endl;
    int ans;
    cin >> ans;
    if (ans == m - a + 1) {
      a = m + 1;
    } else {
      b = m;
    }
  }
  x = a;
  a = 1, b = n;
  while (b - a >= 1) {
    int m = a + (b - a) / 2;
    cout << "? " << 1 << " " << n << " " << a << " " << m << endl;
    int ans;
    cin >> ans;
    if (ans == m - a + 1) {
      a = m + 1;
    } else {
      b = m;
    }
  }
  y = a;

  cout << "! " << x << " " << y << endl;
  return 0;
}