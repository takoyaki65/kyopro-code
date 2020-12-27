#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T &x) {
  return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
inline bool setmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}

template <typename T, typename X>
auto vectors(T a, X x) {
  return vector<T>(x, a);
}

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
  auto cont = vectors(a, y, zs...);
  return vector<decltype(cont)>(x, cont);
}

// combination(L-1, 11)

int main() {
  int n{0}, m{0};
  cin >> n >> m;
  vector<int> va(m+1);
  for(int i = 0; i < m; ++i) {
    cin >> va[i];
    --va[i];
  }
  va[m] = n;
  sort(va.begin(), va.end());
  vector<int> vpan;
  vpan.reserve(m);
  {
    int pa{0};
    for(int i = 0; i < m+1; ++i) {
      int a = va[i];
      if(a - pa > 0) vpan.push_back(a - pa);
      pa = a + 1;
    }
  }

  int width = *min_element(vpan.begin(), vpan.end());
  int num{0};
  for(const int &pan : vpan) {
    //cout << "pan: " << pan << endl;
    num += (pan + width - 1) / width;
  }
  cout << num << endl;
  return 0;
}