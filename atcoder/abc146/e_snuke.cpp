#include <bits/stdc++.h>
using namespace std;
#define repeat(i, n) for (int i = 0; i < (n); ++i)

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    repeat(i, n) cin >> a[i];
    repeat(i, n) a[i]--;
    vector<int> s(n + 1);
    repeat(i, n) {
        s[i + 1] = (s[i] + a[i]) % k;
    }
    map<int, int> mp;
    long long ans = 0;
    queue<int> que;
    repeat(j, n + 1) {
        ans += mp[s[j]];
        mp[s[j]]++;
        que.push(s[j]);
        if (que.size() == k) {
            mp[que.front()]--;
            que.pop();
        }
    }
    cout << ans << endl;
    return 0;
}