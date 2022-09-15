#include <algorithm>
#include <iostream>
using namespace std;

#define MAXN 200010
int n;
int score[MAXN];
int main() {
  cin >> n;

  for (int i = 0; i < n; ++i) {
    int pi;
    cin >> pi;
    for (int dx = -1; dx <= 1; ++dx) {
      int ndx = (dx + n) % n;
      int npi = (pi + ndx) % n;
      int rot = (npi - i + n) % n;
      score[rot] += 1;
      // cout << "i: " << i << " pi: " << pi << " npi: " << npi << " rot: " <<
      // rot
      //      << endl;
    }
  }

  cout << *max_element(score, score + n) << endl;
  return 0;
}