#include <algorithm>
#include <deque>
#include <iostream>
#include <tuple>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
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

// 移動の重みが0か1だから、01BFSかな？
// でもそうすると、意味のないキューが増えそうだから、
// 基本0コストで移動するのを優先して、移動できる場所がなかったらワープに挑戦するようにしよう
// 嘘解放っぽいので、真面目にやる

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int main() {
    int H, W;
    cin >> H >> W;
    int ch, cw, dh, dw;
    cin >> ch >> cw >> dh >> dw;
    --ch, --cw, --dh, --dw;
    vector<string> S(H);
    repeat(i, H) cin >> S[i];
    auto grid = vectors(-1, H, W);
    deque<tuple<int, int, int>> que;
    que.emplace_back(0, ch, cw);
    grid[ch][cw] = 0;
    while (!que.empty()) {
        int d = get<0>(que.back());
        int x = get<1>(que.back());
        int y = get<2>(que.back());
        que.pop_back();
        // コスト0移動
        repeat(i, 4) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
            if (S[nx][ny] == '#') continue;
            if (grid[nx][ny] == -1 || grid[nx][ny] > d) {
                grid[nx][ny] = d;
                que.emplace_back(d, nx, ny);
            }
        }
        // コスト1移動
        repeat_from(nx, x - 2, x + 3) {
            repeat_from(ny, y - 2, y + 3) {
                if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
                if (S[nx][ny] == '#') continue;
                if (grid[nx][ny] == -1 || grid[nx][ny] > d + 1) {
                    grid[nx][ny] = d + 1;
                    que.emplace_front(d + 1, nx, ny);
                }
            }
        }
    }

    cout << grid[dh][dw] << endl;
    return 0;
}