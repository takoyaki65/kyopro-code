// 最大値を求めることは簡単(一番小さい約数から淳に選べばよい)
// 最小値を求めるのはどうするか
#include <bits/stdc++.h>
using namespace std;

map<int64_t, int> prime_factor(int64_t n) {
    map<int64_t, int> ret;
    for (int64_t i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ret[i]++;
            n /= i;
        }
    }
    if (n != 1) ret[n] = 1;
    return ret;
}

int main() {
    int64_t N;
    cin >> N;
    auto p_factor = prime_factor(N);
    long long Max = 1;
    for (auto p : p_factor) {
        Max *= (p.second + 1);
    }
    --Max;
    cout << p_factor.size() << " " << Max << endl;
    return 0;
}