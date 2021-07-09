#include <algorithm>
#include <array>
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
#include <random>
#include <set>
#include <stack>
#include <unordered_map>
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

std::random_device rnd;
std::mt19937 mt(rnd());
std::uniform_int_distribution<> rand0_800(0, 800);
std::uniform_int_distribution<> rand0_100(0, 100);
std::uniform_int_distribution<> rand0_50(0, 50);
std::uniform_int_distribution<> rand0_10(0, 10);
std::uniform_int_distribution<> rand0_5(0, 5);
std::uniform_int_distribution<> rand0_3(0, 3);
std::uniform_int_distribution<> rand1_5(1, 5);
std::uniform_int_distribution<> rand1_10(1, 10);
std::uniform_int_distribution<> rand2_40(2, 40);
std::uniform_int_distribution<> rand1_50(1, 50);
std::uniform_int_distribution<> rand1_100(1, 100);
std::uniform_int_distribution<> rand1_200(1, 200);
std::uniform_int_distribution<> rand1_300(1, 300);
std::uniform_int_distribution<> rand1_800(1, 800);
std::uniform_int_distribution<> rand0_1(0, 1);

const int INF = 20000;

struct TestCase {
  int N, P, K;
  int A[41][41];
  friend ostream& operator<<(ostream& os, const TestCase& tc) {
    os << tc.N << " " << tc.P << " " << tc.K << endl;
    for (int i = 0; i < tc.N; ++i) {
      for (int j = 0; j < tc.N; ++j) {
        os << tc.A[i][j] << " ";
      }
      os << endl;
    }
    return os;
  }
};

TestCase genTestCase() {
  TestCase ret;
  do {
    ret.N = 5;
    ret.P = rand1_10(mt);
    ret.K = 0;
  } while (!(ret.K <= ret.N * (ret.N - 1) / 2));
  for (int i = 0; i < ret.N; ++i) {
    for (int j = i + 1; j < ret.N; ++j) {
      if (rand0_1(mt)) {
        ret.A[i][j] = ret.A[j][i] = rand1_200(mt);
      } else {
        ret.A[i][j] = ret.A[j][i] = -1;
      }
    }
  }
  for (int i = 0; i < ret.N; ++i)
    ret.A[i][i] = 0;
  return ret;
}

struct Answer {
  int lb, ub;
  int ans;
  bool operator==(const Answer& rhs) const {
    return lb == rhs.lb && ub == rhs.ub && ans == rhs.ans;
  }
  bool operator!=(const Answer& rhs) const { return !(*this).operator==(rhs); }
  friend ostream& operator<<(ostream& os, const Answer& rhs) {
    os << "lb: " << rhs.lb << endl;
    os << "ub: " << rhs.ub << endl;
    os << "ans: " << rhs.ans << endl;
    return os;
  }
};

Answer Solver_guchoku(const TestCase& tc) {
  long long B[41][41];
  const int N = tc.N;
  const int P = tc.P;
  const int K = tc.K;
  const auto& A = tc.A;
  int ans = 0;
  int lb = INF + 1000;
  int ub = -1;
  for (int X = 1; X < INF; ++X) {
    // シミュレーション
    repeat(i, N) repeat(j, N) B[i][j] = A[i][j];
    repeat(i, N) repeat(j, N) if (B[i][j] == -1) B[i][j] = X;
    repeat(k, N) repeat(i, N) repeat(j, N) B[i][j] =
        min(B[i][j], B[i][k] + B[k][j]);
    int cnt = 0;
    repeat(i, N) repeat_from(j, i + 1, N) if (B[i][j] <= P) cnt += 1;
    if (cnt == K) {
      ans += 1;
      lb = min(lb, X);
      ub = max(ub, X + 1);
    }
  }
  return {lb, ub, ans};
}

Answer Solver_submit(const TestCase& tc) {
  long long B[41][41];
  const int N = tc.N;
  const int P = tc.P;
  const int K = tc.K;
  const auto& A = tc.A;
  int lb = 0, ub = 0;
  auto check = [&B, &N, &P, &K, &A](int X) -> int {
    repeat(i, N) repeat(j, N) B[i][j] = A[i][j];
    repeat(i, N) repeat(j, N) if (B[i][j] == -1) B[i][j] = X;
    repeat(k, N) repeat(i, N) repeat(j, N) B[i][j] =
        min(B[i][j], B[i][k] + B[k][j]);
    int cnt = 0;
    repeat(i, N) repeat_from(j, i + 1, N) if (B[i][j] <= P) cnt += 1;
    return cnt;
  };
  {
    int left = 0, right = INF;
    while (abs(right - left) > 1) {
      int mid = (left + right) / 2;
      int cnt = check(mid);
      if (cnt > K)
        left = mid;
      else
        right = mid;
    }
    lb = right;
  }

  {
    int left = 0, right = INF;
    while (abs(right - left) > 1) {
      int mid = (left + right) / 2;
      int cnt = check(mid);
      if (cnt >= K)
        left = mid;
      else
        right = mid;
    }
    ub = right;
  }

  int ans = ub - lb;
  return {lb, ub, ans};
}

int main() {
  int test_case_num = 100;
  while (test_case_num--) {
    auto tc = genTestCase();
    auto ans_guchoku = Solver_guchoku(tc);
    auto ans_submit = Solver_submit(tc);

    if (ans_guchoku.ans != ans_submit.ans) {
      cout << "wrong answer generated!" << endl;
      cout << "test case: " << endl;
      cout << tc << endl;
      cout << "correct Answer: " << endl;
      cout << ans_guchoku << endl;
      cout << "wrong_answer: " << endl;
      cout << ans_submit << endl;
    } else {
      cout << "test_case: " << endl;
      cout << tc << endl;
      cout << "Answer(guchoku): " << endl;
      cout << ans_guchoku << endl;
      cout << "Answer(submit): " << endl;
      cout << ans_submit << endl;
    }
  }

  return 0;
}