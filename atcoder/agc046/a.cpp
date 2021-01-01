#include <bits/stdc++.h>
using namespace std;

int main() {
  int x{0};
  cin >> x;
  int k{0};
  while (true) {
    ++k;
    if (k * x % 360) continue;
    cout << k << endl;
    return 0;
  }
  return 0;
}