#include <iostream>
using namespace std;
#define bit(x, i) ((x >> i) & 1)
int func[31][2];
int ans[200001];
int cbit[31];
int main() {
  int n, c;
  cin >> n >> c;
  for (int i = 0; i < 30; ++i)
    func[i][0] = 0, func[i][1] = 1, cbit[i] = bit(c, i);

  for (int idx = 0; idx < n; ++idx) {
    int t, a;
    cin >> t >> a;
    for (int i = 0; i < 30; ++i) {
      int x = bit(a, i);
      if (t == 1)
        func[i][0] = func[i][0] & x, func[i][1] = func[i][1] & x;
      if (t == 2)
        func[i][0] = func[i][0] | x, func[i][1] = func[i][1] | x;
      if (t == 3)
        func[i][0] = func[i][0] ^ x, func[i][1] = func[i][1] ^ x;
      cbit[i] = func[i][cbit[i]];
      ans[idx] |= cbit[i] << i;
    }
  }

  for (int i = 0; i < n; ++i)
    cout << ans[i] << endl;

  return 0;
}