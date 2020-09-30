#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
#define sz(x) int(x.size())
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
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

#define PRINT(X) cout << #X << " : " << X << endl

int main() {
    int H, W;
    cin >> H >> W;
    vector<string> s(H);
    repeat(i, H) cin >> s[i];
    auto visited = vectors(false, H, W);
    long long res = 0;
    repeat(i, H) {
        repeat(j, W) {
            if (visited[i][j]) continue;
            long long b = 0, w = 0;
            visited[i][j] = true;
            queue<pair<int, int>> que;
            que.emplace(i, j);
            while (!que.empty()) {
                int y = que.front().first;
                int x = que.front().second;
                que.pop();
                if (s[y][x] == '.')
                    ++w;
                else
                    ++b;
                repeat(k, 4) {
                    int ny = y + dy[k];
                    int nx = x + dx[k];
                    if (ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
                    if ((!visited[ny][nx]) and s[ny][nx] != s[y][x]) {
                        visited[ny][nx] = true;
                        que.emplace(ny, nx);
                    }
                }
            }
            res += b * w;
        }
    }
    cout << res << endl;
    return 0;
}