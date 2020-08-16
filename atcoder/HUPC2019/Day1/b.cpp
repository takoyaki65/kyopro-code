#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> q(n);
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        q[p - 1] = i;
    }

    string ans;
    stack<int> st;
    int count_closing_parenthesis = 0;
    for (int i = 0; i < n; ++i) {
        ans += "(";
        st.push(q[i]);

        while (st.size() && count_closing_parenthesis == st.top()) {
            ans += ")";
            st.pop();
            count_closing_parenthesis++;
        }
    }
    if (!st.empty()) {
        cout << ":(" << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}