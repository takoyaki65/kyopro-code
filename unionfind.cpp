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
