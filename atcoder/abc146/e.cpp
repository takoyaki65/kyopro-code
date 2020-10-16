#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
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

// S_i := {A_0, A_1, ... , A_(i-1)}の和
// (S_j - S_i)%K == (j - i)
// S_j - S_i == C*K + (j - i)
// S_j == S_i + (j - i) + C*K
// S_j%K == (S_i + (j - i))%K
// (S_j - j)%K == (S_i - i)%K かつ j - i < K

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    repeat(i, N) cin >> A[i];
    vector<long long> S(N + 1);
    repeat(i, N) S[i + 1] = S[i] + A[i];
    //repeat(i, N + 1) cout << (S[i] - i + K) % K << " ";
    cout << endl;
    long long res = 0;
    map<int, int> dict;
    repeat_from(j, 0, N + 1) {
        if (j - K >= 0) {
            int l_key = (S[j - K] - (j - K) + K) % K;
            --dict[l_key];
            if (dict[l_key] <= 0) {
                dict.erase(l_key);
            }
        }
        // j - K < i < j
        int key = (S[j] - j + K) % K;
        auto itr = dict.find(key);
        if (itr != dict.end()) {
            //cout << j << " : " << itr->second << endl;
            res += itr->second;
        }
        ++dict[key];
    }
    cout << res << endl;
    return 0;
}