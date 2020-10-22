#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

template <class T>
inline int sz(T &x) {
    return x.size();
}

template <class T>
inline bool setmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool setmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

#define PRINT(X) cout << #X << " : " << X << endl;

int main() {
    int N;
    while (cin >> N, N) {
        int A, B, C, D;
        cin >> A >> B >> C >> D;
        --A, --B, --C, --D;
        vector<int> x(N + 1), y(N + 1);
        repeat(i, N + 1) {
            cin >> x[i] >> y[i];
            //assert(x[i] >= 1 and x[i] <= 100 and y[i] >= 1 and y[i] <= 100);
            --x[i], --y[i];
        }

        const int INF = 1e9;
        auto grid = vectors(INF, 100, 100);
        auto bfs = [&](int sx, int sy, int gx, int gy) -> int {
            repeat(i, 100) fill(begin(grid[i]), end(grid[i]), INF);
            grid[sy][sx] = 0;
            deque<tuple<int, int, int>> que;
            que.emplace_back(sy, sx, 0);
            while (!que.empty()) {
                auto [y, x, d] = que.front();
                //cout << "y: " << y << " x: " << x << " grid[y][x]: " << grid[y][x] << endl;
                que.pop_front();
                //assert(grid[y][x] != INF);
                repeat(i, 4) {
                    int ny = y + dy[i];
                    int nx = x + dx[i];
                    if (ny < 0 or ny >= 100 or nx < 0 or nx >= 100) continue;
                    int cost = !(B <= ny and ny <= D and A <= nx and nx <= C);
                    //cout << "ny: " << ny << " nx: " << nx << " cost: " << cost << endl;
                    if (grid[ny][nx] > grid[y][x] + cost) {
                        grid[ny][nx] = grid[y][x] + cost;
                        if (cost)
                            que.emplace_back(ny, nx, grid[y][x] + cost);
                        else
                            que.emplace_front(ny, nx, grid[y][x] + cost);
                    }
                }
            }
            return grid[gy][gx];
        };

        int res = 0;
        repeat(i, N) {
            int ret = bfs(x[i], y[i], x[i + 1], y[i + 1]);
            //cout << i << " -> " << i + 1 << " : " << ret << endl;
            res += ret;
        }
        cout << res << endl;
    }
    return 0;
}