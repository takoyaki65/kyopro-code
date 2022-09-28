#include <cassert>
#include <cstdio>
#include <vector>
using namespace std;
long long x[3000], y[3000], r[3000];
vector<int> g[3000];
bool visited[3000];
bool dfs(int v, int goal) {
  visited[v] = true;
  if (v == goal)
    return true;
  for (auto to : g[v]) {
    if (visited[to] != true) {
      if (dfs(to, goal))
        return true;
    }
  }
  return false;
}
int main() {
  int n;
  long long sx, sy, tx, ty;
  scanf("%d", &n);
  scanf("%lld %lld %lld %lld", &sx, &sy, &tx, &ty);
  for (int i = 0; i < n; ++i)
    scanf("%lld %lld %lld", &x[i], &y[i], &r[i]);

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      long long dist =
          (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);

      if (dist <= (r[i] + r[j]) * (r[i] + r[j]) &&
          dist >= (r[i] - r[j]) * (r[i] - r[j])) {
        g[i].push_back(j);
        g[j].push_back(i);
      }
    }
  }

  auto p2c = [&](long long px, long long py) -> int {
    for (int i = 0; i < n; ++i) {
      if ((px - x[i]) * (px - x[i]) + (py - y[i]) * (py - y[i]) ==
          r[i] * r[i]) {
        return i;
      }
    }
    return -1;
  };

  int s = p2c(sx, sy), t = p2c(tx, ty);
  assert(s != -1);
  assert(t != -1);

  // debug
  // for (int i = 0; i < n; ++i) {
  //   printf("g[%d]: ", i);
  //   for (auto to : g[i]) {
  //     printf("%d ", to);
  //   }
  //   printf("\n");
  // }
  // printf("s: %d, t: %d\n", s, t);
  //

  if (dfs(s, t)) {
    printf("Yes\n");
  } else {
    printf("No\n");
  }

  return 0;
}