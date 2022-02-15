#include <iostream>
#include <string>
using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    try {
      long long a, s;
      cin >> a >> s;
      // x + y = (x and y)*2 + (x xor y)
      long long andVal = a;             // x and y
      long long xorVal = s - (a << 1);  // x xor y
      if (xorVal < 0)
        throw string("No");
      for (int i = 0; i <= 60; ++i) {
        if ((andVal >> i) & 1 && (xorVal >> i) & 1) {
          throw string("No");
        }
      }
      throw string("Yes");
    } catch (const string& str) {
      cout << str << endl;
    }
  }
  return 0;
}