#include <bits/stdc++.h>
//https://qiita.com/ysuzuki19/items/d89057d65284ba1a16ac
#define debug(var)                  \
    do {                            \
        std::cout << #var << " : "; \
        view(var);                  \
    } while (0)
template <typename T>
void view(T e) { std::cout << e << std::endl; }

template <typename T>
void view(const std::vector<T>& v) {
    for (const auto& e : v) {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void view(const std::vector<std::vector<T>>& vv) {
    for (const auto& v : vv) {
        view(v);
    }
}

using namespace std;
//yosupo
template <class T>
using V = vector<T>;
template <class T>
using VV = V<V<T>>;
template <class T>
using tpl = tuple<T, T, T>;

// Binary Indexed Tree (BIT)
// https://www.slideshare.net/hcpc_hokudai/binary-indexed-tree
template <typename T>
struct BIT {
   private:
    vector<T> array;
    const int n;

   public:
    // 初期化
    BIT(int _n) : array(_n + 1, 0), n(_n) {}

    // 一番目からi番目までの累積和を求める
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += array[i];
            i -= i & -i;  // LSB減算
        }
        return s;
    }

    // [i, j]の要素の累積和
    T sum(int i, int j) {
        T ret_i = sum(i - 1);
        T ret_j = sum(j);
        return ret_j - ret_i;
    }

    // i番目に要素xを追加
    void add(int i, T x) {
        while (i <= n) {
            array[i] += x;
            i += i & -i;  // LSB加算
        }
    }
};

int main() {
    int N, Q;
    cin >> N >> Q;
    V<int> C(N + 1);  // BITに合わせて1-indexed
    for (int i = 1; i <= N; ++i) {
        cin >> C[i];
    }
    V<tpl<int>> Query;
    for (int i = 0; i < Q; ++i) {
        int l, r;
        cin >> l >> r;
        Query.emplace_back(r, l, i);
    }
    sort(Query.begin(), Query.end());

    V<int> ans(Q);
    // 左からk番目までに、色iの玉が存在するか、
    // 存在するなら最も右にいる玉の場所を格納
    V<int> MRB(N + 1, -1);
    BIT<int> Fenwrick_Tree(N);
    int R = 1;

    for (auto q : Query) {
        int r = get<0>(q);
        int l = get<1>(q);
        int idx = get<2>(q);
        for (; R <= r; ++R) {
            int c = C[R];
            if (MRB[c] != -1) {
                assert(Fenwrick_Tree.sum(MRB[c], MRB[c]) == 1);
                assert(C[MRB[c]] == c);
                Fenwrick_Tree.add(MRB[c], -1);
            }
            Fenwrick_Tree.add(R, 1);
            MRB[c] = R;
        }
        ans[idx] = Fenwrick_Tree.sum(l, r);
    }

    for (int i = 0; i < Q; ++i) {
        cout << ans[i] << endl;
    }

    return 0;
}