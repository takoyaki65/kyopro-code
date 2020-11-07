#include <bits/stdc++.h>
using namespace std;
#define repeat(i, n) for (int i = (0); i < (n); ++i)

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

int main() {
    int w, h, n, d, b;
    while (cin >> w >> h >> n >> d >> b, w | h | n | d | b) {
        --b;
        vector<int> x_vec(n), y_vec(n);
        repeat(i, n) cin >> x_vec[i] >> y_vec[i];
        repeat(i, n)-- x_vec[i], --y_vec[i];

        vector<vector<int>> grid(h, vector<int>(w, -1));
        repeat(i, n) grid[y_vec[i]][x_vec[i]] = i;

        vector<bool> used(n);
        used[b] = true;
        stack<int> stk;
        stk.push(b);
        while (!stk.empty()) {
            int bomb = stk.top();
            stk.pop();
            int cx = x_vec[bomb];
            int cy = y_vec[bomb];
            for (int len = 1; len <= d; ++len) {
                repeat(k, 4) {
                    int nx = cx + len * dx[k];
                    int ny = cy + len * dy[k];
                    if (nx < 0 or nx >= w or ny < 0 or ny >= h) continue;
                    if (grid[ny][nx] != -1) {
                        int id = grid[ny][nx];
                        if (!used[id]) {
                            used[id] = true;
                            stk.push(id);
                        }
                    }
                }
            }
        }
        int res = 0;
        repeat(i, n) if (used[i])++ res;
        cout << res << endl;
    }
    return 0;
}