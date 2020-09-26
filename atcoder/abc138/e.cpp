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

// (sの中のtの転倒数？)×|s| + tの最後の文字列のsでのインデックス
// 転倒数じゃない、map[t_i] = iとしたとき、
// sの中でtに含まれる文字をsにある順に並べて{k_i}としたとき
// map[k_i] > map[k_{i+1}]となっている個数

int main() {
    string S, T;
    cin >> S >> T;

    int N = S.size();
    int M = T.size();
    const int alpha = 'z' - 'a' + 1;
    vector<vector<int>> Sid(alpha);
    repeat(i, N) {
        Sid[S[i] - 'a'].push_back(i);
    }

    auto next_ch = vectors(-1, N, alpha);
    /* 
    repeat(i, N) {
        repeat(j, alpha) {
            if (Sid[j].empty()) continue;
            auto itr = lower_bound(Sid[j].begin(), Sid[j].end(), i + 1);
            if (itr != Sid[j].end()) {
                next_ch[i][j] = *itr;
            } else {
                itr = Sid[j].begin();
                next_ch[i][j] = *itr;
            }
        }
    }
 */
    //cout << "done" << endl;

    int cur = 0;
    int s = 0;
    long long res = 0;
    while (cur < M) {
        int v = T[cur] - 'a';
        if (cur == 0) {
            if (Sid[v].empty()) {
                cout << -1 << endl;
                //cout << "begin" << endl;
                return 0;
            }
            auto itr = Sid[v].begin();
            res = *itr + 1;
            s = *itr;
            //cout << "s: " << s << endl;
        } else {
            if (Sid[v].empty()) {
                cout << -1 << endl;
                return 0;
            }
            if (next_ch[s][v] == -1) {
                auto itr = lower_bound(Sid[v].begin(), Sid[v].end(), s + 1);
                if (itr != Sid[v].end()) {
                    next_ch[s][v] = *itr;
                } else {
                    itr = Sid[v].begin();
                    next_ch[s][v] = *itr;
                }
            }

            int to = next_ch[s][v];
            if (to == -1) {
                cout << -1 << endl;
                return 0;
            }
            //assert(S[to] == T[cur]);
            if (to > s) {
                res += to - s;
                s = to;
            } else {
                res += (N - 1) - s + to + 1;
                s = to;
            }
        }
        ++cur;
    }

    cout << res << endl;
    return 0;
}