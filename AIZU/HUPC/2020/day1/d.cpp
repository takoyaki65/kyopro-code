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

template <typename T>
T cross(T a, T b, T c, T d) {
    return a * d - b * c;
}

int main() {
    int T;
    cin >> T;
    vector<int> gp(20010);
    while (T--) {
        int N;
        cin >> N;
        vector<long long> x(N), y(N);
        repeat(i, N) cin >> x[i] >> y[i];
        if (N <= 3) {
            cout << "Yes" << endl;
            continue;
        }
        bool flg = false;
        repeat(i, 3) {
            repeat(j, N) gp[j] = 0;
            // 方向ベクトル i -> (i + 1)%3
            int f1 = i;
            int t1 = (i + 1) % 3;
            int num1 = 2, num2 = 0;
            gp[f1] = gp[t1] = 1;
            repeat(j, N) {
                if (gp[j]) continue;
                // (x[t1] - x[f1], y[t1] - y[f1]) cross (x[j] - x[f1], y[j] - y[f1])
                if (cross(x[t1] - x[f1], y[t1] - y[f1], x[j] - x[f1], y[j] - y[f1]) == 0LL) {
                    gp[j] = 1;
                    ++num1;
                }
            }
            int f2 = -1;
            int t2 = -1;
            repeat(j, N) {
                if (gp[j]) continue;
                if (f2 == -1) {
                    f2 = j;
                    gp[j] = 2;
                    ++num2;
                } else if (t2 == -1) {
                    t2 = j;
                    gp[j] = 2;
                    ++num2;
                } else {
                    assert(f2 != -1 && t2 != -1);
                    if (cross(x[t2] - x[f2], y[t2] - y[f2], x[t1] - x[f1], y[t1] - y[f1]) != 0LL) {
                        break;
                    }
                    // (x[t2] - x[f2], y[t2] - y[f2]) cross (x[j] - x[f2], y[j] - y[f2])
                    if (cross(x[t2] - x[f2], y[t2] - y[f2], x[j] - x[f2], y[j] - y[f2]) == 0LL) {
                        gp[j] = 2;
                        ++num2;
                    }
                }
            }
            if (num1 + num2 == N) {
                if (t2 == -1 || f2 == -1) {
                    flg = true;
                    break;
                }
                if (cross(x[t2] - x[f2], y[t2] - y[f2], x[t1] - x[f1], y[t1] - y[f1]) == 0LL) {
                    flg = true;
                    break;
                }
            }
        }
        if (flg)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}