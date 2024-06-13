#include <cstdio>
#include <string>
#include <vector>
using namespace std;

template <typename T, typename X>
auto vectors(T a, X x) {
  return vector<T>(x, a);
}

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
  auto cont = vectors(a, y, zs...);
  return vector<decltype(cont)>(x, cont);
}

// x^k
int pow(int x, int k) {
  int res = 1;
  while (k > 0) {
    if (k & 1)
      res *= x;
    x *= x;
    k >>= 1;
  }
  return res;
}

int main() {
  int n, l;
  scanf("%d %d", &n, &l);
  vector<string> arr(n, string(l, '0'));

  // We regard (arr[i][0], arr[i][1], ..., arr[i][l-1]) as a number in base 3.
  // e.g. (1, 2, 0) -> 1 * 3^2 + 2 * 3^1 + 0 * 3^0 = 9 + 6 + 0 = 15

  // Prepare 200_(3), 201_(3), ..., 2*3^(l-1) + n-1 and store them in the arr.
  const int base = pow(3, l - 1);
  for (int i = 0; i < n; ++i) {
    int x = 2 * base + i;
    for (int j = l - 1; j >= 0; --j) {
      arr[i][j] = (x % 3) + '0';
      x /= 3;
    }
  }

  // Output the modified arr.
  // 0 -> 1, 1 -> 2, 2 -> 0
  const char conv1[] = {'1', '2', '0'};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l; ++j) {
      putchar(conv1[arr[i][j] - '0']);
    }
    putchar('\n');
  }

  // Output the modified arr.
  // 0 -> 2, 1 -> 0, 2 -> 1
  const char conv2[] = {'2', '0', '1'};
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < l; ++j) {
      putchar(conv2[arr[i][j] - '0']);
    }
    putchar('\n');
  }

  // Output the arr.
  for (int i = 0; i < n; ++i) {
    puts(arr[i].c_str());
  }

  return 0;
}