#include <algorithm>
#include <iostream>
#include <list>
#include <set>
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
    int N;
    cin >> N;
    vector<list<int>> T(N);
    repeat(i, N) {
        int K;
        cin >> K;
        repeat(j, K) {
            int t;
            cin >> t;
            T[i].push_back(t);
        }
    }
    set<pair<int, int>> S1, S2;
    repeat(i, N) {
        S1.emplace(T[i].front(), i);
        if (T[i].size() >= 2) {
            S2.emplace(max(T[i].front(), *(++T[i].begin())), i);
        }
    }
    // T_ijはすべて異なるので、同じ消費期限が複数,,,なんてことはない
    int M;
    cin >> M;
    while (M--) {
        int a;
        cin >> a;
        //cout << "test" << endl;
        if (a == 1) {
            auto p = *(--S1.end());
            cout << p.first << endl;
            S1.erase(p);
            S2.erase(p);
            int id = p.second;
            T[id].pop_front();
            if (!T[id].empty()) {
                S1.emplace(T[id].front(), id);
            }
            if (T[id].size() >= 2) {
                S2.emplace(max(T[id].front(), *(++T[id].begin())), id);
            }
        } else {
            pair<int, int> p = {-1, -1};
            bool flg = true;
            if (!S1.empty()) {
                setmax(p, *(--S1.end()));
            }
            if (!S2.empty()) {
                auto q = *(--S2.end());
                if (p < q) {
                    setmax(p, q);
                    flg = false;
                }
            }
            cout << p.first << endl;
            S1.erase(p);
            S2.erase(p);
            int id = p.second;
            if (flg) {
                T[id].pop_front();
            } else {
                T[id].erase(++T[id].begin());
            }
            if (!T[id].empty()) {
                S1.emplace(T[id].front(), id);
            }
            if (T[id].size() >= 2) {
                S2.emplace(max(T[id].front(), *(++T[id].begin())), id);
            }
        }
    }
    return 0;
}