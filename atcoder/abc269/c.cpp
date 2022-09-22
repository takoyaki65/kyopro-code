#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef unsigned long long ull;
int main() {
  ull n;
  cin >> n;
  vector<ull> pset;
  // https://ark4rk.hatenablog.com/entry/2018/03/07/230257
  for (ull t = n;; t = (t - 1) & n) {
    pset.push_back(t);
    if (t == 0)
      break;
  }
  sort(pset.begin(), pset.end());
  for (auto s : pset) {
    cout << s << endl;
  }
  return 0;
}