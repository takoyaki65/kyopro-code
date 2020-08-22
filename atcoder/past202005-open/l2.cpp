#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> T;
set<tuple<int, int, int>> S1, S2;

void f(set<tuple<int, int, int>> &s, int t, int i, int j) {
    s.erase({t, i, j});
    for (int k = j + 1; k < T.at(i).size(); k++) {
        if (!s.count({T.at(i).at(k), i, k}) && T.at(i).at(k) != -1) {
            s.insert({T.at(i).at(k), i, k});
            break;
        }
    }
}

int main() {
    int N, M;
    cin >> N;
    T.resize(N);
    for (int i = 0, k; i < N && cin >> k; i++) {
        for (int j = 0, t; j < k && cin >> t; j++) {
            if (j == 0) S1.insert({t, i, j});
            if (j <= 1) S2.insert({t, i, j});
            T.at(i).push_back(t);
        }
    }
    cin >> M;
    for (int a; cin >> a;) {
        auto [t, i, j] = (a == 1) ? *rbegin(S1) : *rbegin(S2);
        cout << t << "\n";
        T.at(i).at(j) = -1;
        if (S1.count({t, i, j})) f(S1, t, i, j);
        f(S2, t, i, j);
    }
}
