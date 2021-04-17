#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T& x) {
  return x.size();
}

template <class T>
inline bool setmax(T& a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T& a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}

template <typename T, typename X>
auto vectors(T a, X x) {
  return vector<T>(x, a);
}

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
  auto cont = vectors(a, y, zs...);
  return vector<decltype(cont)>(x, cont);
}

template <typename T>
using vec3 = array<T, 3>;

template <typename T>
class Mat3x3 {
 public:
  typedef vec3<T> row_type;

 private:
  // row-major
  row_type data[3];

 public:
  const row_type& operator[](size_t index) const { return data[index]; }
  row_type& operator[](size_t index) { return data[index]; }

  Mat3x3 operator*(const Mat3x3& rhs) {
    Mat3x3 ret;
    for (int row = 0; row < 3; ++row) {
      for (int col = 0; col < 3; ++col) {
        ret[row][col] = (*this)[row][0] * rhs[0][col] +
                        (*this)[row][1] * rhs[1][col] +
                        (*this)[row][2] * rhs[2][col];
      }
    }
    return ret;
  }

  Mat3x3() {
    data[0] = {1, 0, 0};
    data[1] = {0, 1, 0};
    data[2] = {0, 0, 1};
  }

  Mat3x3(initializer_list<row_type> init) {
    auto itr = init.begin();
    data[0] = *(itr++);
    data[1] = *(itr++);
    data[2] = *itr;
  }

  template <typename U>
  vec3<U> operator*(const vec3<U>& rhs) {
    return {data[0][0] * rhs[0] + data[0][1] * rhs[1] + data[0][2] * rhs[2],
            data[1][0] * rhs[0] + data[1][1] * rhs[1] + data[1][2] * rhs[2],
            data[2][0] * rhs[0] + data[2][1] * rhs[1] + data[2][2] * rhs[2]};
  }
};

typedef Mat3x3<long long> Mat;
typedef vec3<long long> vec;

const Mat identity = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
const Mat op1 = {{0, 1, 0}, {-1, 0, 0}, {0, 0, 1}};
const Mat op2 = {{0, -1, 0}, {1, 0, 0}, {0, 0, 1}};

Mat op3(long long p) {
  return {{-1, 0, 2LL * p}, {0, 1, 0}, {0, 0, 1}};
}

Mat op4(long long p) {
  return {{1, 0, 0}, {0, -1, 2LL * p}, {0, 0, 1}};
}

const int MAX_N = 200010;
const int MAX_M = 200010;

vec pos[MAX_N];
Mat acum[MAX_M];

int n, m, q;

void print_mat(const Mat& matrix) {
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      cout << matrix[row][col] << " ";
    }
    cout << endl;
  }
}

int main() {
  cin >> n;
  repeat(i, n) {
    int x, y;
    cin >> x >> y;
    pos[i] = {x, y, 1};
  }

  cin >> m;
  acum[0] = identity;
  for (int i = 1; i <= m; ++i) {
    int op, p;
    cin >> op;
    switch (op) {
      case 1:
        acum[i] = op1;
        break;
      case 2:
        acum[i] = op2;
        break;
      case 3:
        cin >> p;
        acum[i] = op3(p);
        break;
      case 4:
        cin >> p;
        acum[i] = op4(p);
      default:
        break;
    }
  }

  // accumulate matrix
  for (int i = 1; i <= m; ++i) {
    acum[i] = acum[i] * acum[i - 1];
  }

  cin >> q;
  repeat(i, q) {
    int a, b;
    cin >> a >> b;
    --b;
    vec ans = acum[a] * pos[b];
    cout << ans[0] << " " << ans[1] << endl;
  }

  return 0;
}