#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
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

int main() {
    int N, K;
    string S;
    cin >> N >> K >> S;
    const int M = 'z' - 'a' + 1;
    vector<set<int>> alphabet(M);
    repeat(i, N) alphabet[S[i] - 'a'].insert(i);
    int err = 0;
    repeat(i, N) {
        if (err >= K) break;
        repeat(j, M) {
            if (alphabet[j].empty()) continue;
            int k = *alphabet[j].rbegin();
            if (S[i] != S[k] && err + 2 > K) break;
            swap(S[i], S[k]);
            if (S[i] != S[k]) {
                alphabet[j].erase(k);
                alphabet[S[i] - 'a'].insert(k);
                err += 2;
            }
            alphabet[S[k] - 'a'].erase(i);
            break;
        }
    }
    cout << S << endl;
    return 0;
}