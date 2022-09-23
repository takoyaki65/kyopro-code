#include <iostream>
#include <map>
using namespace std;

int main() {
  map<int, int> dict;
  for (int i = 0; i < 5; ++i) {
    int x;
    cin >> x;
    dict[x] += 1;
  }

  if (dict.size() == 2) {
    int a, b;
    for (auto [key, val] : dict) {
      a = b;
      b = val;
    }
    if (a > b)
      swap(a, b);
    if (a == 2 && b == 3) {
      cout << "Yes" << endl;
      return 0;
    }
  }
  cout << "No" << endl;
  return 0;
}
