#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
  int n;
  string s;
  cin >> n;
  map<string, int> dict;
  while (n--) {
    cin >> s;
    auto itr = dict.find(s);
    if (itr == dict.end()) {
      cout << s << endl;
      dict[s] = 1;
    } else {
      cout << s << "(" << (*itr).second << ")" << endl;
      (*itr).second += 1;
    }
  }
  return 0;
}