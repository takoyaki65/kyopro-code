#include <cstdio>
using namespace std;
#define bit(x, i) ((x >> i) & 1)
int w[200010];
int to[200010][42];
long long num[200010];
int main() {
  int n, q;
  long long x;
  scanf("%d %d %lld", &n, &q, &x);
  for (int i = 0; i < n; ++i)
    scanf("%d", &w[i]);

  {
    long long w_sum = 0;
    for (int i = 0; i < n; ++i)
      w_sum += w[i];
    long long offset = (x / w_sum) * n;
    x = x % w_sum;
    long long acum = 0;
    long long sz = 0;
    for (int l = 0, r = 0; l < n; ++l) {
      while (acum < x) {
        acum += w[r];
        r = (r + 1) % n;
        sz += 1;
      }
      to[l][0] = r;
      num[l] = offset + sz;
      // l -> l + 1
      acum -= w[l];
      sz -= 1;
    }
  }

  // printf("to[..][0]: ");
  // for (int i = 0; i < n; ++i)
  //   printf("%d ", to[i][0]);
  // printf("\n");
  // printf("num[..]: ");
  // for (int i = 0; i < n; ++i)
  //   printf("%lld ", num[i]);
  // printf("\n");

  for (int lv = 1; lv < 42; ++lv) {
    for (int i = 0; i < n; ++i) {
      to[i][lv] = to[to[i][lv - 1]][lv - 1];
    }
  }

  while (q--) {
    long long k;
    scanf("%lld", &k);
    k -= 1;
    int cur = 0;
    for (int lv = 0; lv < 42; ++lv) {
      if (bit(k, lv)) {
        cur = to[cur][lv];
      }
    }

    printf("%lld\n", num[cur]);
  }

  return 0;
}