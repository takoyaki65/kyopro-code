#include <iostream>
#include <map>
#include <string>
using namespace std;
int main() {
  map<string, int> dict;
  dict["Monday"] = 5;
  dict["Tuesday"] = 4;
  dict["Wednesday"] = 3;
  dict["Thursday"] = 2;
  dict["Friday"] = 1;
  string str;
  cin >> str;
  if (dict.count(str) != 0) {
    cout << dict[str] << endl;
  }
  return 0;
}