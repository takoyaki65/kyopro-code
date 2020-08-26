#include <algorithm>
#include <cmath>
#include <iostream>
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

const int INF = 1e9 + 7;

int main() {
    using pii = pair<int, int>;
    int N, K;
    cin >> N >> K;
    vector<int> x(N), y(N);
    repeat(i, N) cin >> x[i] >> y[i];

    vector<pair<pii, pii>> Lines;
    repeat(i, N) {
        repeat_from(j, i + 1, N) {
            int a = y[j] - y[i],
                b = x[j] - x[i],
                c = x[j] * y[i] - x[i] * y[j],
                d = x[j] - x[i];
            if (b == 0) {
                a = 0;
                c = x[i];
                d = INF;
            } else {
                if (a == 0) {
                    b = 1;
                    c = INF;
                    d = y[i];
                } else {
                    long long g = __gcd(a, b);
                    a /= g;
                    b /= g;
                    if (c == 0) {
                        d = 0;
                    } else {
                        long long l = __gcd(c, d);
                        c /= l;
                        d /= l;
                    }
                }
            }
            Lines.emplace_back(make_pair(a, b), make_pair(c, d));
        }
    }
    sort(Lines.begin(), Lines.end());
    int res = 1;
    repeat_from(i, 1, Lines.size()) {
        if (Lines[i] == Lines[i - 1])
            ++res;
        else
            res = 1;
        if (res >= K * (K - 1) / 2) {
            cout << 1 << endl;
            return 0;
        }
    }
    cout << 0 << endl;
    return 0;
}