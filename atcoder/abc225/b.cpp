#include <bits/stdc++.h>
using namespace std;

int in[100010];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    in[a] += 1, in[b] += 1;
  }
  int leaf = 0;
  for (int i = 0; i < n; ++i) {
    if (in[i] == 1)
      leaf += 1;
  }
  if (leaf == n - 1)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;
}