// メモ、参考になった
//https://atcoder.jp/contests/past202005-open/submissions/16815194
// #define _GLIBCXX_DEBUG
#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using pll = pair<ll, ll>;
using vl = vector<ll>;
using vvl = vector<vl>;
using vb = vector<bool>;
using vvb = vector<vb>;
#define rep0(TMS) for (int CNT = 0; CNT < (int)(TMS); CNT++)
#define rep(CNT, GOAL) for (int CNT = 0; CNT < (int)(GOAL); CNT++)
#define rep2(CNT, START, GOAL) for (int CNT = (int)(START); CNT < (int)(GOAL); CNT++)
#define rep3(CNT, START, GOAL) for (int CNT = (int)(START); CNT > (int)(GOAL); CNT--)
#define all(CONT) begin(CONT), end(CONT)
template <typename T>
bool chmax(T &a, const T &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <typename T>
bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
void prec(const int &DIG) {
    cout << fixed << setprecision(DIG);
    cerr << fixed << setprecision(DIG);
}
template <typename T>
void CERR(const T &ELEM) { cerr << ELEM; }
#define dbl(OBJ)          \
    cerr << #OBJ << ": "; \
    CERR(OBJ);            \
    cerr << "\n"
template <typename T, typename... Ts>
void CERR(const T &FIRST, const Ts &... REST) {
    CERR(FIRST);
    cerr << ", ";
    CERR(REST...);
}
#define dbs(...)                           \
    cerr << "(" << #__VA_ARGS__ << "): ("; \
    CERR(__VA_ARGS__);                     \
    cerr << ")\n"
#define itrep(ITR, CONT) for (auto ITR = begin(CONT); ITR != end(CONT); ITR++)
template <typename T>
void CERR(const vector<T> &VEC) {
    cerr << "{ ";
    itrep(ITR, VEC) {
        CERR(*ITR);
        cerr << ", ";
    }
    cerr << "}";
}
#define YN(FLG) cout << (FLG ? "YES" : "NO") << "\n"
#define Yn(FLG) cout << (FLG ? "Yes" : "No") << "\n"
#define yn(FLG) cout << (FLG ? "yes" : "no") << "\n"

// #include <atcoder/all>

// using namespace atcoder;

// const ll INF = LONG_LONG_MAX;
const int INF = INT_MAX;
// const ll MOD = 1000000007; // 998244353;

int N, Q;
vi a;
set<int> s;  // a[i]>a[i+1]なるi(0<=i<N-1)の集合

void myswap(int x) {
    if (s.count(x))
        s.erase(x);  // a[x]>a[x+1] -> a[x]<a[x+1]
    else
        s.insert(x);  // a[x]<a[x+1] -> a[x]>a[x+1]
    swap(a[x], a[x + 1]);
    if (0 < x) {
        if (s.count(x - 1) and a[x - 1] < a[x])
            s.erase(x - 1);
        else if (!s.count(x - 1) and a[x - 1] > a[x])
            s.insert(x - 1);
    }
    if (x < N - 2) {
        if (s.count(x + 1) and a[x + 1] < a[x + 2])
            s.erase(x + 1);
        else if (!s.count(x + 1) and a[x + 1] > a[x + 2])
            s.insert(x + 1);
    }
}

void ans() {
    rep(i, N) {
        if (i) cout << " ";
        cout << a[i];
    }
    cout << endl;
}

int main() {
    // 0-ind
    cin >> N >> Q;
    a = vi(N);
    rep(i, N) a[i] = i + 1;
    while (Q--) {
        int t, x, y;
        cin >> t >> x >> y;
        // dbs(t, x, y);
        x--;
        y--;           // 0-ind
        if (t == 1) {  // (a[x-1],a[x],a[x+1],a[x+2]) -> (a[x-1],a[x+1],a[x],a[x+2])
            myswap(x);
        } else if (t == 2) {
            while (true) {
                set<int>::iterator it = s.lower_bound(x);
                if (it == end(s) or *it >= y) break;
                myswap(*it);
            }
        }
        // dbl(a);
        // for (int x : s) cout << ++x << ", ";
        // cout << endl;
    }
    ans();
}
