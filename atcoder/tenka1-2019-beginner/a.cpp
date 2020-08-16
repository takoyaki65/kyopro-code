#include <bits/stdc++.h>
using namespace std;

// A <= C <= B
// B <= C <= A
int main() {
    int A, B, C;
    cin >> A >> B >> C;
    if ((A <= C && C <= B) || (B <= C && C <= A)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}