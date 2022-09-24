#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
  string s;
  cin >> s;
  map<char, int> dict;
  for (const char& ch : s)
    dict[ch] += 1;
  for (const auto& [ch, k] : dict) {
    if (k == 1) {
      cout << ch << endl;
      return 0;
    }
  }
  cout << -1 << endl;
  return 0;
}