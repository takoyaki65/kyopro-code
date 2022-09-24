#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main() {
  int n;
  string s;
  unordered_map<string, int> dict;
  cin >> n;
  while (n--) {
    cin >> s;
    int k = dict[s];
    if (k == 0) {
      cout << s << "\n";
    } else {
      cout << s << "(" << k << ")\n";
    }
    dict[s] += 1;
  }
}