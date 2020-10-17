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

const int cost[] = {2, 5, 5, 4, 5, 6, 3, 7, 6};

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> A(M);
    repeat(i, M) cin >> A[i];
    vector<string> nums(N + 1);
    vector<int> dp(N + 1, -1);
    dp[0] = 0;
    nums[0] = "";
    repeat_from(i, 1, N + 1) {
        repeat(k, M) {
            int j = A[k] - 1;
            int from = i - cost[j];
            if (from < 0) continue;
            if (dp[from] == -1) continue;
            if (dp[i] < dp[from] + 1) {
                dp[i] = dp[from] + 1;
                nums[i] = nums[from] + char(j + '1');
            } else if (dp[i] == dp[from] + 1) {
                sort(rbegin(nums[i]), rend(nums[i]));
                string l = nums[from] + char(j + '1');
                sort(rbegin(l), rend(l));
                if (nums[i] < l) {
                    nums[i] = l;
                }
            }
        }
    }

    string res = nums[N];
    sort(rbegin(res), rend(res));
    cout << res << endl;
    return 0;
}