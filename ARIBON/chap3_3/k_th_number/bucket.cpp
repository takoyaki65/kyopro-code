// WAが抜けない、、
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;

// Bucket size
const int B = 900;
const int MAX_N = 100010;
const int MAX_M = 50010;

// input
int N, M;
int A[MAX_N];
int I[MAX_M], J[MAX_M], K[MAX_M];

// Aをソートしたもの
int nums[MAX_N];
// 各バケットをソートしたもの
vector<int> bucket[MAX_N / B];

void solve() {
    repeat(i, N) {
        bucket[i / B].push_back(A[i]);
        nums[i] = A[i];
    }
    sort(nums, nums + N);
    // B個に満たない最後のバケットをソートしていないが、問題ない
    repeat(i, N / B) {
        sort(bucket[i].begin(), bucket[i].end());
    }

    repeat(i, M) {
        // [l, r)のk番目の数を求める
        int l = I[i], r = J[i] + 1, k = K[i];

        int lb = -1, ub = N - 1;
        while (ub - lb > 1) {
            int md = (lb + ub) / 2;
            int x = nums[md];
            // c := 区間に存在するx以下の数
            int tl = l, tr = r, c = 0;

            // バケットをはみ出す部分
            while (tl < tr and tl % B != 0)
                if (A[tl++] <= x) c++;
            while (tl < tr and tr % B != 0)
                if (A[--tr] <= x) c++;

            // バケットごと
            while (tl < tr) {
                //assert(tl % B == 0);
                int b = tl / B;
                c += upper_bound(bucket[b].begin(), bucket[b].end(), x) - bucket[b].begin();
                tl += B;
            }

            if (c >= k)
                ub = md;
            else
                lb = md;
        }
        cout << nums[ub] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    repeat(i, N) cin >> A[i];
    repeat(i, M) {
        cin >> I[i] >> J[i] >> K[i];
        --I[i], --J[i];
    }
    solve();
    return 0;
}