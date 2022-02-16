#include <iostream>
using namespace std;
char str[500010];
int deq[1000100];
int begin_itr = 500050, end_itr = 500050;
void push_front(int v) {
  deq[--begin_itr] = v;
}
void push_back(int v) {
  deq[end_itr++] = v;
}

int main() {
  int n;
  cin >> n >> str;
  push_back(n);
  for (int i = n - 1; i >= 0; --i) {
    if (str[i] == 'R') {
      push_front(i);
    } else {
      push_back(i);
    }
  }

  for (int i = begin_itr; i < end_itr; ++i) {
    if (i == end_itr - 1)
      cout << deq[i] << endl;
    else
      cout << deq[i] << " ";
  }
  return 0;
}