#include <bits/stdc++.h>
using namespace std;

// https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
/**
 * @brief Union-Find
 *
 * @note This data structure supports the following methods:
 *      - unite(x, y): unite two sets
 *      - find(k): find the root of set
 *      - size(k): get the size of set
 */
struct UnionFind {
  vector<int> data;

  /**
   * @brief Construct a new Union Find object
   *
   * @param sz  The size of set (0-indexed)
   * @return UnionFind object
   */
  UnionFind(int sz) { data.assign(sz, -1); }

  /**
   * @brief Unite two sets
   *
   * @param x  The index of set(0-indexed)
   * @param y  The index of set(0-indexed)
   * @return true  The two sets are united
   * @return false  The two sets are not united
   * @note O(α(N))
   */
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y)
      return (false);
    if (data[x] > data[y])
      swap(x, y);
    data[x] += data[y];
    data[y] = x;
    return (true);
  }

  /**
   * @brief Find the root of set
   *
   * @param k  The index of set(0-indexed)
   * @return int  The root of set
   */
  int find(int k) {
    if (data[k] < 0)
      return (k);
    return (data[k] = find(data[k]));
  }

  /**
   * @brief Get the size of set
   *
   * @param k  The index of set(0-indexed)
   * @return int  The size of set
   */
  int size(int k) { return (-data[find(k)]); }

  /**
   * @brief Check if two sets are same
   *
   * @param x  The index of set(0-indexed)
   * @param y  The index of set(0-indexed)
   * @return true  The two sets are same
   * @return false  The two sets are not same
   */
  bool same(int x, int y) { return find(x) == find(y); }
};

/**
 * @brief Weighted Union-Find
 * @note This data structure supports the following methods:
 *       - init(n, SUM_UNITY): construct n sets that all elements are disjoint
 *       - root(x): get the root of x's set
 *       - weight(x): get the weight of x
 *       - diff(x, y): get the weight(y) - weight(x)
 *       - merge(x, y, w): merge x's set and y's set so that
 *                         weight(y) - weight(x) = w
 *       - is_same(x, y): check if x and y are in the same set
 *       ref: https://qiita.com/drken/items/cce6fc5c579051e64fab
 *
 * @param Abel  The type of weight (e.g. int, float, double)
 *              Abel must have the properties of Abelian group:
 *              1. Commutativity: a + b = b + a
 *              2. Associativity: (a + b) + c = a + (b + c)
 *              3. Identity element: a + 0 = a
 *              4. Inverse element: a + (-a) = 0
 */
template <class Abel>
struct WeightedUnionFind {
  vector<int> par;
  vector<int> rank;
  vector<Abel> diff_weight;

  WeightedUnionFind(int n = 1, Abel SUM_UNITY = 0) { init(n, SUM_UNITY); }

  void init(int n = 1, Abel SUM_UNITY = 0) {
    par.resize(n);
    rank.resize(n);
    diff_weight.resize(n);
    for (int i = 0; i < n; ++i)
      par[i] = i, rank[i] = 0, diff_weight[i] = SUM_UNITY;
  }

  int root(int x) {
    if (par[x] == x) {
      return x;
    } else {
      int r = root(par[x]);
      diff_weight[x] += diff_weight[par[x]];
      return par[x] = r;
    }
  }

  Abel weight(int x) {
    root(x);
    return diff_weight[x];
  }

  bool is_same(int x, int y) { return root(x) == root(y); }

  /**
   * @brief Merge x's set and y's set so that weight(y) - weight(x) = w
   * @note O(α(N))
   * @param x  The index of set(0-indexed)
   * @param y  The index of set(0-indexed)
   * @param w  The weight of edge
   * @return true  The two sets are united
   * @return false  The two sets are already united
   */
  bool merge(int x, int y, Abel w) {
    w += weight(x), w -= weight(y);
    x = root(x), y = root(y);
    if (x == y)
      return false;
    if (rank[x] < rank[y])
      swap(x, y), w = -w;
    // At this point, rank[x] >= rank[y]
    if (rank[x] == rank[y])
      ++rank[x];
    par[y] = x;
    diff_weight[y] = w;
    return true;
  }

  /**
   * @brief Get the weight(y) - weight(x)
   * @note O(α(N))
   * @param x  The index of set(0-indexed)
   * @param y  The index of set(0-indexed)
   * @return Abel  The weight(y) - weight(x)
   */
  Abel diff(int x, int y) { return weight(y) - weight(x); }
};

int main() {
  int n, q;
  scanf("%d %d", &n, &q);
  WeightedUnionFind<int> uf(n);
  while (q--) {
    int com, x, y, z;
    scanf("%d %d %d", &com, &x, &y);
    if (com == 0) {
      scanf("%d", &z);
      // a_y is greater than a_x by z
      uf.merge(x, y, z);
    } else {
      if (uf.is_same(x, y)) {
        // print the difference between a_y and a_x
        printf("%d\n", uf.diff(x, y));
      } else {
        printf("?\n");
      }
    }
  }
  return 0;
}
