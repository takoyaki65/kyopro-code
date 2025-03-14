#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (n); ++i)
using ll = long long;

const ll INF = 1e18;

struct Edge {
  ll cost;
  int to;
};

struct DistGroup {
  ll dist;
  int group;
  bool operator<(const DistGroup &other) const {
    if (dist != other.dist) return dist < other.dist;
    return group < other.group;
  }
  bool operator>(const DistGroup &other) const {
    if (dist != other.dist) return dist > other.dist;
    return group > other.group;
  }
  bool operator==(const DistGroup &other) const {
    return dist == other.dist && group == other.group;
  }
};

using State = pair<DistGroup, int>;

struct Top2 {
  DistGroup a, b;
  Top2() : a({INF, -1}), b({INF, -1}) {}
  bool add(DistGroup x) {
    if (x.dist < a.dist) {
      if (x.group == a.group)
        a = x;
      else
        b = a, a = x;
    } else if (x.dist < b.dist) {
      if (a.group == x.group)
        return false;
      b = x;
    } else
      return false;
    return true;
  }
  bool contain(DistGroup x) const {
    return a == x || b == x;
  }
  ll get(int x) {
    if (a.group == x) return b.dist;
    else return a.dist;
  }
};

int main() {
  int n, m, k, l;
  cin >> n >> m >> k >> l;
  vector<int> groupId(n);
  rep(i, n) cin >> groupId[i];
  vector<int> sourceList(l);
  rep(i, l) cin >> sourceList[i], --sourceList[i];
  vector<vector<Edge>> g(n);
  rep(i, m) {
    int a, b, c;
    cin >> a >> b >> c;
    --a, --b;
    g[a].push_back({c, b});
    g[b].push_back({c, a});
  }

  vector<Top2> dp(n);
  priority_queue<State, vector<State>, greater<State>> pq;
  auto push = [&](int v, DistGroup d) {
    if (!dp[v].add(d)) return;
    pq.emplace(d, v);
  };
  for (int v: sourceList) push(v, DistGroup{0, groupId[v]});
  while (!pq.empty()) {
    auto [distGrp, v] = pq.top(); pq.pop();
    if (!dp[v].contain(distGrp)) continue;
    auto [dist, group] = distGrp;
    for (auto [cost, to]: g[v]) {
      push(to, DistGroup{dist + cost, group});
    }
  }
  rep(i, n) {
    ll ans = dp[i].get(groupId[i]);
    if (ans == INF) ans = -1;
    printf("%lld%c", ans, i == n - 1 ? '\n' : ' ');
  }
}