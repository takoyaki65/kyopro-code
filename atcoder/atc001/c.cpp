// 非再帰FFT
// アルゴリズムイントロダクション第3版: p760 参照
#include <bits/stdc++.h>
using namespace std;

namespace FFT {
const double pi = acos(-1);
int bit_reverse(int bit, int lgn) {
  int l = 0, r = lgn - 1;
  int b1 = 0, b2 = 0;
  while (l < r) {
    b1 = (bit >> l) & 1;
    b2 = (bit >> r) & 1;
    if (b1)
      bit |= 1 << r;
    else
      bit &= ~(1 << r);
    if (b2)
      bit |= 1 << l;
    else
      bit &= ~(1 << l);
    l += 1, r -= 1;
  }
  return bit;
}

vector<complex<double>> bit_reverse_copy(const vector<complex<double>>& a,
                                         int lgn) {
  vector<complex<double>> A(a.size());
  const int n = a.size();
  for (int i = 0; i < n; ++i) {
    A[bit_reverse(i, lgn)] = a[i];
  }
  return A;
}

vector<complex<double>> fft(const vector<complex<double>>& a,
                            int lgn,
                            bool inv) {
  auto A = bit_reverse_copy(a, lgn);
  const int n = a.size();
  for (int s = 1; s <= lgn; ++s) {
    const int m = 1 << s;
    const complex<double> wm(cos(2 * pi / m), (inv ? -1 : 1) * sin(2 * pi / m));
    for (int k = 0; k < n; k += m) {
      complex<double> w = 1;
      for (int j = 0; j < m / 2; ++j) {
        auto t = w * A[k + j + m / 2];
        auto u = A[k + j];
        A[k + j] = u + t;
        A[k + j + m / 2] = u - t;
        w = w * wm;
      }
    }
  }
  return A;
}

int least_2pow(int x) {
  int ret = 1;
  while (ret < x)
    ret <<= 1;
  return ret;
}

vector<double> multiply(const vector<double>& _X, const vector<double>& _Y) {
  vector<complex<double>> X(_X.size()), Y(_Y.size());
  const int n = least_2pow(X.size() + Y.size() - 1);
  X.resize(n);
  Y.resize(n);
  for (int i = 0; i < _X.size(); ++i)
    X[i] = _X[i];
  for (int i = 0; i < _Y.size(); ++i)
    Y[i] = _Y[i];

  const int lgn = __builtin_ctz(n);
  // cout << "n: " << n << " lgn: " << lgn << endl;
  vector<complex<double>> fA(n);
  auto fX = fft(X, lgn, false);
  auto fY = fft(Y, lgn, false);
  for (int i = 0; i < n; ++i) {
    fA[i] = fX[i] * fY[i];
  }
  auto A = fft(fA, lgn, true);
  for (int i = 0; i < n; ++i) {
    A[i] /= n;
  }
  vector<double> ret(n);
  for (int i = 0; i < n; ++i)
    ret[i] = A[i].real();
  return ret;
}

};  // namespace FFT

int main() {
  int n;
  cin >> n;
  vector<double> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i)
    cin >> a[i] >> b[i];
  auto c = FFT::multiply(a, b);
  for (int i = 1; i <= 2 * n; ++i)
    printf("%.0lf\n", c[i]);
  return 0;
}