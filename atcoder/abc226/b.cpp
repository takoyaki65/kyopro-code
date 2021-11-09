#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  set<vector<int>> dict;
  for (int i = 0; i < n; ++i) {
    int l;
    cin >> l;
    vector<int> key(l);
    for (int j = 0; j < l; ++j)
      cin >> key[j];
    dict.insert(key);
  }
  cout << dict.size() << endl;
}