#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
using namespace std;
const double pi = acos(-1);
int main() {
  double a, b, d;
  cin >> a >> b >> d;
  auto x = a + b * 1i;
  auto rot = cos(d * pi / 180.0) + sin(d * pi / 180.0) * 1i;
  auto y = rot * x;
  cout << fixed << setprecision(15) << y.real() << " " << y.imag() << endl;
  return 0;
}