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

int N, M;
int A[301][301];
int S[301];

void swapRow(int x, int y) {
  repeat(i, M) swap(A[x][i], A[y][i]);
}

void Xor(int* P, int* Q) {
  repeat(i, M) P[i] ^= Q[i];
}

bool isZero(int* P) {
  repeat(i, M) if (P[i] != 0) return false;
  return true;
}

void printMat() {
  cout << "A: " << endl;
  repeat(i, N) {
    repeat(j, M) { cout << A[i][j] << " "; }
    cout << endl;
  }
}

int main() {
  cin >> N >> M;
  repeat(i, N) {
    int T;
    cin >> T;
    repeat(j, T) {
      int Tj;
      cin >> Tj;
      --Tj;
      A[i][Tj] = 1;
    }
  }
  repeat(i, M) cin >> S[i];

  // printMat();

  int pos = 0;
  repeat(i, M) {
    bool found = false;
    repeat_from(j, pos, N) {
      if (A[j][i] == 1) {
        swapRow(pos, j);
        found = true;
        break;
      }
    }
    if (found) {
      repeat(j, N) {
        if (j != pos && A[j][i] == 1)
          Xor(A[j], A[pos]);
      }

      if (S[i] == 1)
        Xor(S, A[pos]);

      ++pos;

      // printMat();
    }
  }

  if (isZero(S)) {
    int ans = 1;
    for (int i = pos; i < N; ++i) {
      ans = ans * 2 % 998244353;
    }
    cout << ans << endl;
  } else {
    cout << 0 << endl;
  }

  return 0;
}