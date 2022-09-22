#include <iostream>
#include <string>
using namespace std;
string s[12];
int main() {
  for (int i = 0; i < 10; ++i)
    cin >> s[i];
  int a = -1, b = -1, c = -1, d = -1;
  for (int i = 0; i < 10; ++i) {
    if (s[i] == "..........") {
      if (a != -1 && b == -1)
        b = i;
    } else {
      if (a == -1)
        a = i + 1;
      if (c == -1 && d == -1) {
        for (int j = 0; j < 10; ++j) {
          if (s[i][j] == '.') {
            if (c != -1 && d == -1)
              d = j;
          } else {
            if (c == -1)
              c = j + 1;
          }
        }
      }
    }
  }
  if (b == -1)
    b = 10;
  if (d == -1)
    d = 10;
  cout << a << " " << b << endl;
  cout << c << " " << d << endl;
  return 0;
}