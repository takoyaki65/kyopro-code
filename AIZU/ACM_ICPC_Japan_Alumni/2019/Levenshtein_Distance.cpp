#include <bits/stdc++.h>
using namespace std;

// https://rosettacode.org/wiki/Levenshtein_distance#C.2B.2B

size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2) {
    const size_t m(s1.size());
    const size_t n(s2.size());

    // 一方が空文字列なら、他方の長さが求める距離
    if (m == 0) return n;
    if (n == 0) return m;

    vector<size_t> costs(n + 1);
    for (size_t k = 0; k <= n; ++k) costs[k] = k;

    size_t i = 0;
    for (auto it1 = begin(s1); it1 != end(s1); ++it1, ++i) {
        costs[0] = i + 1;
        size_t corner = i;

        size_t j = 0;
        for (auto it2 = begin(s2); it2 != end(s2); ++it2, ++j) {
            size_t upper = costs[j + 1];
            if (*it1 == *it2) {
                costs[j + 1] = corner;
            } else {
                size_t t = min(upper, corner);
                costs[j + 1] = min(costs[j], t) + 1;
            }
            corner = upper;
        }
    }

    size_t result = costs[n];
    return result;
}

int main() {
    string s0 = "rosettacode";
    string s1 = "raisethysword";
    cout << "distance between " << s0 << " and " << s1 << " : "
         << uiLevenshteinDistance(s0, s1) << std::endl;

    return 0;
}