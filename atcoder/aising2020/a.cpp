#include <bits/stdc++.h>
using namespace std;

int main() {
    int L, R, d;
    cin >> L >> R >> d;
    cout << R / d - (L - 1) / d << endl;
    return 0;
}