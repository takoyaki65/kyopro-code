#include <iostream>
#include <set>

int main() {
  int x;
  std::set<int> dict;
  for (int i = 0; i < 5; ++i) {
    std::cin >> x;
    dict.insert(x);
  }
  std::cout << dict.size() << std::endl;
  return 0;
}