#include <iostream>
#include <string>

using namespace std;

int main() {
  string s, t;
  cin >> s >> t;
  if (s.size() > t.size()) {
    cout << "No" << endl;
    return 0;
  }
  if (s == t.substr(0, s.size())) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
  return 0;
}