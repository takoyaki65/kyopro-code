#include <iostream>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
#define bit_stand(n, k) ((n >> k) & 1)
using namespace std;

typedef long long ll;

const int MAX_N = 500010;
// 入力
int n, k;
ll a[MAX_N];

ll dp[MAX_N + 1];
ll S[MAX_N + 1];  // aの累積和
int deq[MAX_N];   // deque

ll f(int j, int x) {
  return -a[j] * x + dp[j] - S[j] + a[j] * j;
}

bool check(int f1, int f2, int f3) {
  ll a1 = -a[f1], b1 = dp[f1] - S[f1] + a[f1] * f1;
  ll a2 = -a[f2], b2 = dp[f2] - S[f2] + a[f2] * f2;
  ll a3 = -a[f3], b3 = dp[f3] - S[f3] + a[f3] * f3;
  return (a2 - a1) * (b3 - b2) >= (b2 - b1) * (a3 - a2);
}

void solve() {
  for (int i = 0; i < n; ++i) {
    S[i + 1] = S[i] + a[i];
  }

  int s = 0, t = 1;
  deq[0] = 0;

  dp[0] = 0;

  for (int i = k; i <= n; ++i) {
    // 直線1, 2, ... , k-1の切片は∞なので最小値を取る候補にならない
    if (i - k >= k) {
      // 末尾から最小値をとる可能性がなくなったものを取り除く
      while (s + 1 < t && check(deq[t - 2], deq[t - 1], i - k))
        t--;

      // dequeにi-kを追加
      deq[t++] = i - k;
    }

    // 先頭が最小値でなければ取り除く
    while (s + 1 < t && f(deq[s], i) >= f(deq[s + 1], i))
      s++;

    dp[i] = S[i] + f(deq[s], i);
  }

  cout << dp[n] << endl;
}

int main() {
  int test_case_num = 0;
  cin >> test_case_num;
  while (test_case_num--) {
    cin >> n >> k;
    repeat(i, n) cin >> a[i];
    solve();
  }
  return 0;
}