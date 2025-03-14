#include <algorithm>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const long long INF = 1e18;

struct Edge {
  int to, cost;
};

using Graph = vector<vector<Edge>>;

int main() {
  int n, m, k, l;
  scanf("%d %d %d %d", &n, &m, &k, &l);
  vector<int> groupId(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &groupId[i]);
  }
  vector<int> sourceList(l);
  for (int i = 0; i < l; ++i) {
    scanf("%d", &sourceList[i]);
    sourceList[i]--;
  }
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    u--;
    v--;
    graph[u].push_back({v, c});
    graph[v].push_back({u, c});
  }

  // dictionary-order: (dist, groupId)
  struct distPerGroup {
    long long dist;
    int groupId;
    bool operator<(const distPerGroup& other) const {
      return dist < other.dist ||
             (dist == other.dist && groupId < other.groupId);
    }
    bool operator>(const distPerGroup& other) const {
      return dist > other.dist ||
             (dist == other.dist && groupId > other.groupId);
    }
    bool operator==(const distPerGroup& other) const {
      return dist == other.dist && groupId == other.groupId;
    }
  };

  // distPerGroup[nodeId] := shortest distance to nodeId per each group
  vector<set<distPerGroup>> distPerGroup(n);

  struct State {
    long long cost;
    int src_groupId;
    int current_nodeId;
    bool operator<(const State& other) const { return cost > other.cost; }
  };
  priority_queue<State> que;
  for (int i = 0; i < l; ++i) {
    int s = sourceList[i];
    distPerGroup[s].insert({0, groupId[s]});
    que.push({0, groupId[s], s});
  }

  while (!que.empty()) {
    State state = que.top();
    que.pop();

    auto [cost, src_groupId, current_nodeId] = state;
    long long current_dist = INF;
    for (auto [dist, groupId] : distPerGroup[current_nodeId]) {
      if (groupId == src_groupId) {
        current_dist = dist;
        break;
      }
    }

    if (current_dist < cost) {
      continue;
    }

    for (auto [to, c] : graph[current_nodeId]) {
      long long dest_dist = INF;
      for (auto it = distPerGroup[to].begin(); it != distPerGroup[to].end();
           ++it) {
        if (it->groupId == src_groupId) {
          dest_dist = it->dist;
          break;
        }
      }
      long long new_dist = current_dist + c;
      if (dest_dist == INF) {
        distPerGroup[to].insert({new_dist, src_groupId});
      } else if (dest_dist > new_dist) {
        distPerGroup[to].erase({dest_dist, src_groupId});
        distPerGroup[to].insert({new_dist, src_groupId});
      } else {
        continue;
      }

      // shrink the set to keep at most 2 elements;
      while (distPerGroup[to].size() > 2) {
        distPerGroup[to].erase(--distPerGroup[to].end());
      }

      if (distPerGroup[to].find({new_dist, src_groupId}) !=
          distPerGroup[to].end()) {
        que.push({new_dist, src_groupId, to});
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    long long ans = INF;
    int dest_groupId = groupId[i];

    // debug
    // printf("nodeId: %d\n", i);
    // for (auto [dist, src_groupId] : distPerGroup[i]) {
    //   printf("dist: %lld, src_groupId: %d\n", dist, src_groupId);
    // }

    for (auto [dist, src_groupId] : distPerGroup[i]) {
      if (src_groupId == dest_groupId) {
        continue;
      }
      ans = min(ans, dist);
    }
    if (ans == INF) {
      printf("-1 ");
    } else {
      printf("%lld ", ans);
    }
  }
  printf("\n");
}