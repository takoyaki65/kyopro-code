#include <bits/stdc++.h>
using namespace std;

int ld(string &s, string &t, int s_cur, int t_cur, vector<vector<int>> &memo) {
    if (s_cur == int(s.size())) return int(t.size()) - t_cur;
    if (t_cur == int(t.size())) return int(s.size()) - s_cur;

    if (s[s_cur] == t[t_cur]) return ld(s, t, s_cur + 1, t_cur + 1, memo);

    if (memo[s_cur][t_cur] != -1) return memo[s_cur][t_cur];

    int l1 = ld(s, t, s_cur, t_cur + 1, memo);
    int l2 = ld(s, t, s_cur + 1, t_cur, memo);
    int l3 = ld(s, t, s_cur + 1, t_cur + 1, memo);

    return memo[s_cur][t_cur] = 1 + min(l1, min(l2, l3));
}

int main() {
    string s0 = "rosettacode";
    string s1 = "raisethysword";
    vector<vector<int>> memo(s0.size() + 1, vector<int>(s1.size(), -1));
    cout << "distance between " << s0 << " and " << s1 << " : "
         << ld(s0, s1, 0, 0, memo) << std::endl;
    return 0;
}