#include <bits/stdc++.h>
using namespace std;
int a[1000], b[1000];
bool selected[1000];
typedef pair<int, int> pii;
int main() {
  int n, x, y, z;
  cin >> n >> x >> y >> z;
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i)
    cin >> b[i];
  auto cmp = [](const pii& l, const pii& r) -> bool {
    return l.first > r.first || (l.first == r.first && l.second < r.second);
  };
  {
    vector<pii> math;
    for (int i = 0; i < n; ++i)
      math.push_back({a[i], i});
    sort(math.begin(), math.end(), cmp);
    for (int i = 0; i < x; ++i) {
      selected[math[i].second] = true;
    }
  }

  {
    vector<pair<int, int>> english;
    for (int i = 0; i < n; ++i)
      if (!selected[i])
        english.push_back({b[i], i});
    sort(english.begin(), english.end(), cmp);
    for (int i = 0; i < y; ++i) {
      selected[english[i].second] = true;
    }
  }

  {
    vector<pair<int, int>> score;
    for (int i = 0; i < n; ++i)
      if (!selected[i])
        score.push_back({a[i] + b[i], i});
    sort(score.begin(), score.end(), cmp);
    for (int i = 0; i < z; ++i) {
      selected[score[i].second] = true;
    }
  }

  for (int i = 0; i < n; ++i)
    if (selected[i])
      cout << i + 1 << endl;
  return 0;
}