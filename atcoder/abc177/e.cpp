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

const int MAX_AI = 1000010;
#define PRINT(X) cout << #X << " : " << X << endl

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    vector<int> prime(MAX_AI);
    for (int i = 0; i < MAX_AI; ++i) {
        prime[i] = i;
    }
    for (int i = 2; i < MAX_AI; ++i) {
        if (prime[i] == i) {
            for (int j = 2 * i; j < MAX_AI; j += i) {
                if (prime[j] == j) prime[j] = i;
            }
        }
    }

    vector<bool> used(MAX_AI, false);
    bool flg = false;
    for (int x : A) {
        while (x > 1) {
            if (used[prime[x]]) {
                flg = true;
                break;
            }
            used[prime[x]] = true;
            int tmp = prime[x];
            while (x % tmp == 0) x /= tmp;
        }
        if (flg) break;
    }
    if (!flg) {
        cout << "pairwise coprime" << endl;
        return 0;
    }

    int res = __gcd(A[0], A[1]);
    for (int i = 2; i < A.size(); ++i) {
        res = __gcd(res, A[i]);
    }
    if (res == 1) {
        cout << "setwise coprime" << endl;
    } else {
        cout << "not coprime" << endl;
    }
    return 0;
}