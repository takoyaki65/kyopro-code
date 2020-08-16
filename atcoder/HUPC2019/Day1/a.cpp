#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    set<int> a, b;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.insert(x);
    }
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        b.insert(x);
    }
    int A = 0, B = 0;
    set<int> And, Or;
    for (auto p : a) {
        if (b.count(p)) {
            And.insert(p);
            ++A;
        }
        Or.insert(p);
    }
    for (auto p : b) {
        Or.insert(p);
    }

    cout << And.size() << " " << Or.size() << endl;
    for (auto p : And) {
        cout << p << endl;
    }
    for (auto p : Or) {
        cout << p << endl;
    }
    return 0;
}