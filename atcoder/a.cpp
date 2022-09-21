#include <iostream>
#include <string>
using namespace std;
int main() {
  string s;
  cin >> s;
  int l = s.size();
  cout << s[l / 2] << endl;
  return 0;
}