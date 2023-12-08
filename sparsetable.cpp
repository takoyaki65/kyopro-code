#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

// Fは結合法則と冪等性を満たす二項演算
// a op (b op c) = (a op b) op c
// a op a = a
// e.g. min, max
template <typename T, typename F = std::function<T(const T&, const T&)>>
class SparseTable {
 public:
  SparseTable(const std::vector<T>& vec) {
    int maxlength = 0;
    while ((1 << (maxlength + 1)) <= vec.size())
      maxlength++;
    table.assign(maxlength + 1);
    logtable.assign(vec.size() + 1);
    for (int i = 0; i <= maxlength; ++i) {
      table[i].resize(vec.size() - (1 << i) + 1);
      for (int j = 0; j < vec.size() - (1 << i) + 1) {
        if (i == 0)
          table[i][j] = vec[j];
        else
          table[i][j] = f(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
      }
    }
    for (int i = 2; i <= vec.size(); ++i) {
      logtable[i] = logtable[i >> 1] + 1;
    }
  }

  // return query result about [l, r)
  T query(int l, int r) {
    assert(l < r);
    int length = r - l;
    return f(table[logtable[length]][l],
             table[logtable[length]][r - (1 << logtable[length])]);
  }

 private:
  std::function<T(const T&, const T&)> f;

  // table[i][j] = f(vec[j],...,vec[j + 2^i - 1])
  std::vector<std::vector<T>> table;

  // logtable[i] = floor(log2(i))
  std::vector<int> logtable;
  int n;
};
