#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))

int main() {
  int N, M, Q;
  cin >> N >> M;
  vector<vector<int>> G(N);
  repeat(i, M) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
  cin >> Q;
  vector<int> x(Q), y(Q);
  repeat(i, Q) {
    cin >> x[i] >> y[i];
    --x[i];
  }

  int B = int(sqrt(2 * M));
  vector<int> large;
  repeat(i, N) {
    if (G[i].size() >= B)
      large.push_back(i);
  }
  vector<vector<bool>> link(N, vector<bool>(large.size(), false));
  repeat(i, large.size()) {
    for (int j : G[large[i]]) {
      link[j][i] = true;
    }
    link[large[i]][i] = true;
  }
  vector<int> update(N, -1);
  vector<int> update_large(large.size(), -1);
  repeat(i, Q) {
    int last = update[x[i]];
    repeat(j, large.size()) {
      if (link[x[i]][j]) {
        last = max(last, update_large[j]);
      }
    }
    cout << (last != -1 ? y[last] : 1) << endl;
    if (G[x[i]].size() < B) {
      update[x[i]] = i;
      for (int j : G[x[i]]) {
        update[j] = i;
      }
    } else {
      int ptr = find(large.begin(), large.end(), x[i]) - large.begin();
      update_large[ptr] = i;
    }
  }

  return 0;
}