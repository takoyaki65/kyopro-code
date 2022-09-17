#include <iostream>
#include <string>
using namespace std;
int arr[7] = {1, 1, 2, 2, 2, 1, 1};
int loc[10] = {3, 2, 4, 1, 3, 5, 0, 2, 4, 6};
int main() {
  string s;
  cin >> s;

  if (s[0] == '1') {
    cout << "No" << endl;
    return 0;
  }

  for (int i = 0; i < 10; ++i) {
    int pin = 1 - (s[i] - '0');
    arr[loc[i]] -= pin;
  }

  // for (int i = 0; i < 7; ++i) {
  //   cout << "arr[" << i << "] : " << arr[i] << endl;
  // }

  for (int i = 0; i < 7; ++i) {
    for (int j = i + 2; j < 7; ++j) {
      for (int k = i + 1; k < j; ++k) {
        if (arr[i] > 0 && arr[j] > 0 && arr[k] == 0) {
          cout << "Yes" << endl;
          return 0;
        }
      }
    }
  }

  cout << "No" << endl;
  return 0;
}