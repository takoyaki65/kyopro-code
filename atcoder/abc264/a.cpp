#include <iostream>
#include <string>
using namespace std;

int main() {
  int l, r;
  cin >> l >> r;
  cout << string("atcoder").substr(l - 1, r - l + 1) << endl;
  return 0;
}