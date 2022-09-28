#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
int main() {
  string s, t;
  cin >> s >> t;
  auto s2r = [](const string& str) -> vector<pair<char, int>> {
    vector<pair<char, int>> strv;
    for (const char& ch : str) {
      if (strv.empty()) {
        strv.push_back({ch, 1});
      } else {
        if (strv.back().first == ch) {
          strv.back().second += 1;
        } else {
          strv.push_back({ch, 1});
        }
      }
    }
    return strv;
  };
  auto sv = s2r(s), tv = s2r(t);
  if (sv.size() != tv.size()) {
    cout << "No" << endl;
    return 0;
  }

  int size = sv.size();
  for (int i = 0; i < size; ++i) {
    if (sv[i].first != tv[i].first) {
      cout << "No" << endl;
      return 0;
    }

    if (sv[i].second == tv[i].second) {
      continue;
    } else if (sv[i].second < tv[i].second && sv[i].second >= 2) {
      continue;
    } else {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;
  return 0;
}