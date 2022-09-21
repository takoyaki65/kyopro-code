#include <iomanip>
#include <iostream>
using namespace std;

double f[110];
int main() {
  int n;
  cin >> n;
  // f[1] = 1/6*1 + 1/6*2 + 1/6*3 + 1/6*4 + 1/6*5 + 1/6*6 = 3.5
  f[1] = 3.5;
  for (int i = 2; i <= n; ++i) {
    f[i] = (max(1.0, f[i - 1]) + max(2.0, f[i - 1]) + max(3.0, f[i - 1]) +
            max(4.0, f[i - 1]) + max(5.0, f[i - 1]) + max(6.0, f[i - 1])) /
           6.0;
  }

  cout << fixed << setprecision(10) << f[n] << endl;
  return 0;
}