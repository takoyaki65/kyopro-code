#include <bits/stdc++.h>
using namespace std;
int main() {
  string S;
  cin >> S;
  sort(S.begin(), S.end());
  set<string> dict;
  do {
    dict.insert(S);
  } while (next_permutation(S.begin(), S.end()));
  cout << dict.size() << endl;
}