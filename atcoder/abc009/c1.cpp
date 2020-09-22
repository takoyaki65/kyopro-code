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
    int M = 'z' - 'a' + 1;
    vector<int> alphabet(M, 0);
    repeat(i, N) alphabet[S[i] - 'a']++;
    vector<int> Ss = alphabet;
    string T = "";
    int err = 0;
    while (T.size() < S.size()) {
        for (int i = 0; i < M; ++i) {
            if (alphabet[i] > 0) {
                int tail = T.size();
                char ch = i + 'a';
                if (ch != S[tail]) ++err;
                alphabet[ch - 'a']--;
                Ss[S[tail] - 'a']--;
                int num = 0;
                for (int j = 0; j < M; ++j) {
                    num += min(alphabet[j], Ss[j]);
                }
                if ((N - tail - 1) - num + err <= K) {
                    T += ch;
                    break;
                } else {
                    alphabet[ch - 'a']++;
                    Ss[S[tail] - 'a']++;
                    if (ch != S[tail]) --err;
                }
            }
        }
    }
    cout << T << endl;
    return 0;
}