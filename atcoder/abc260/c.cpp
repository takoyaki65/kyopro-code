#include <iostream>
using namespace std;
long long red[11], blue[11];
int main() {
  int n, x, y;
  cin >> n >> x >> y;
  red[n] = 1;
  for (int i = n; i >= 2; --i) {
    red[i - 1] += red[i];
    blue[i] += red[i] * x;
    // red[i] = 0;
    red[i - 1] += blue[i];
    blue[i - 1] += blue[i] * y;
    // blue[i] = 0;
  }
  cout << blue[1] << endl;
}