#include <iostream>
#define MOD 998244353
using namespace std;
int main() {
  long long n;
  cin >> n;
  while (n < 0)
    n += MOD;
  n %= MOD;
  cout << n << endl;
  return 0;
}