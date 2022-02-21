#include <bits/stdc++.h>
using namespace std;

#define MAXV 10000000
int memo[MAXV + 10];
int N;
int a;

int mySwap(int v) {
  int a = v / 10;
  int b = v % 10;
  while (v >= 10) {
    v /= 10;
    b *= 10;
  }
  return a + b;
}

int main() {
  cin >> a >> N;
  memset(memo, -1, sizeof(memo));
  queue<int> que;
  memo[1] = 0;
  que.push(1);
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    if ((long long)a * v <= MAXV && memo[a * v] == -1) {
      memo[a * v] = memo[v] + 1;
      que.push(a * v);
    }
    if (v >= 10 && (v % 10) != 0) {
      int swapVal = mySwap(v);
      if (swapVal <= MAXV && memo[swapVal] == -1) {
        // printf("swap %d -> %d\n", v, swapVal);
        memo[swapVal] = memo[v] + 1;
        que.push(swapVal);
      }
    }
  }
  cout << memo[N] << endl;
  return 0;
}