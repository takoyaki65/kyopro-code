#include <iostream>
#include <string>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long a, s;
    cin >> a >> s;
    // x + y = (x and y)*2 + (x xor y)
    long long andVal = a;             // x and y
    long long xorVal = s - (a << 1);  // x xor y
    if (xorVal < 0) {
      cout << "No" << endl;
      continue;
    }
    bool exist = true;
    for (int i = 0; i <= 60; ++i) {
      if ((andVal >> i) & 1 && (xorVal >> i) & 1) {
        exist = false;
        break;
      }
    }
    if (exist)
      cout << "Yes" << endl;
    else
      cout << "No" << endl;
  }
  return 0;
}