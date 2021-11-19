#include <bits/stdc++.h>
using namespace std;

int main() {
  string S;
  cin >> S;
  int n = S.size();
  if (n < 3) {
    string s = S.substr(n - 2, 2);
    if (s == "er") {
      cout << "er" << endl;
    }
  } else {
    string er = S.substr(n - 2, 2);
    string ist = S.substr(n - 3, 3);
    if (er == "er") {
      cout << er << endl;
    } else if (ist == "ist") {
      cout << ist << endl;
    }
  }
  return 0;
}