#include <bits/stdc++.h>
using namespace std;

template <int um>
class UF {
   public:
    vector<int> par, rank;
    UF() {
        rank = vector<int>(um, 0);
        for (int i = 0; i < um; ++i) par.push_back(i);
    }

    int operator[](int x) { return (par[x] == x) ? (x) : (par[x] = operator[](par[x])); }
    int operator()(int x, int y) {
        if ((x = operator[](x)) == (y = operator[](y))) return x;
        if (rank[x] < rank[y]) return par[x] = y;
        rank[x] += rank[x] == rank[y];
        return par[y] = x;
    }
};

UF<500000> uf;

int N, M;
long long D[202020];               // D[i] := 頂点iに設定された値
pair<int, int> P[202020];          // P[i] := (頂点に設定された値, 頂点番号)
vector<pair<int, int>> E[101010];  // E[i][j] := 頂点iのj番目の辺(行先,インデックス)
int ret[202020], fix[202020];      // ret[i] := 辺iの重み   fix[x] := 辺xを設定したか
string S;

void dfs(int cur, int pre, int i) {
    if (i)
        S[cur] = 'B';
    else
        S[cur] = 'W';
    for (auto e : E[cur]) {
        if (e.first != pre && ret[e.second] < (1 << 30)) dfs(e.first, cur, i ^ 1);
    }
}

void solve() {
    int i, j, k, l, r, x, y;
    string s;

    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> D[i];
        P[i] = {D[i], i};
    }
    for (int i = 0; i < M; ++i) {
        cin >> x >> y;
        E[x - 1].push_back({y - 1, i});
        E[y - 1].push_back({x - 1, i});
        ret[i] = 1 << 30;
    }
    sort(P, P + N);
    for (int i = 0; i < N; ++i) {
        x = P[i].second;
        for (auto e : E[x]) {
            if (uf[e.first] != uf[x] && (D[e.first] == D[x] || (D[e.first] < D[x] && fix[e.first]))) {
                ret[e.second] = D[x];
                if (D[e.first] == D[x]) fix[e.first] = 1;
                fix[x] = 1;
                uf(x, e.first);
            }
        }
    }

    int num = 0;
    for (int i = 0; i < N; ++i)
        if (uf[i] == i) num++;
    if (num > 1) {
        cout << -1 << endl;
        return;
    }

    S.resize(N);
    dfs(0, 0, 0);

    cout << S << endl;
    for (int i = 0; i < M; ++i) {
        if (ret[i] == 1 << 30) ret[i] = 1000000000;
        cout << ret[i] << endl;
    }
}