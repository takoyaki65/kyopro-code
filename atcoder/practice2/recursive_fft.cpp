#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using complex_t = std::complex<float>;
using seq = std::vector<complex_t>;

// recursive fft
template <bool Regular>
seq rec_fft(const seq& a) {
  std::size_t n = a.size();
  if (n == 1)
    return a;
  complex_t omega_n(std::cos(2 * M_PI / n), std::sin(2.0 * M_PI / n)),
      omega = 1.0;
  seq A(n / 2), B(n / 2);
  for (std::size_t i = 0; i < n / 2; ++i) {
    if constexpr (Regular) {
      A[i] = a[i * 2];
      B[i] = a[i * 2 + 1];
    } else {
      A[i] = complex_t(a[i * 2].real(), -a[i * 2].imag());
      B[i] = complex_t(a[i * 2 + 1].real(), -a[i * 2 + 1].imag());
    }
  }

  A = rec_fft<true>(A);
  B = rec_fft<true>(B);
  seq r(n);
  for (std::size_t i = 0; i < n / 2; ++i) {
    r[i] = A[i] + omega * B[i];
    r[i + n / 2] = A[i] - omega * B[i];
    omega *= omega_n;
  }
  if constexpr (!Regular) {
    for (auto& i : r) {
      i /= n;
    }
  }
  return r;
}

int main() {
  // 入力例
  std::vector<float> input = {0, 1, 2, 3, 4, 5, 6, 7};

  // 複素数列に変換
  seq input_complex(input.size());
  for (std::size_t i = 0; i < input.size(); ++i) {
    input_complex[i] = input[i];
  }

  // 再帰fft
  seq result_rec_fft = rec_fft<true>(input_complex);
  std::cout << "Recursive-FFT" << std::endl;
  for (auto& n : result_rec_fft) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  // 復元
  seq rev = rec_fft<false>(result_rec_fft);
  std::cout << "Inverse-FFT" << std::endl;
  for (auto& n : rev) {
    std::cout << n << " ";
  }

  std::cout << std::endl;
  return 0;
}