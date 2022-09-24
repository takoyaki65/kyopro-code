#include <iostream>
using namespace std;

int main() {
  int y;
  cin >> y;
  int k = 2 - (y % 4);
  if (k < 0)
    k += 4;
  cout << y + k << endl;
  return 0;
}