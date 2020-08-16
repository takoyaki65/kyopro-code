#include <bits/stdc++.h>
using namespace std;

int P, Q, R;

int eval(string &S, int &cur) {
    if (S[cur] == '(') {
        int a = eval(S, ++cur);
        char op = S[cur];
        int b = eval(S, ++cur);
        int res = 0;
        if (op == '*') {
            res = min(a, b);
        } else {  // S[cur] == '+'
            if (a == 2 || b == 2) {
                res = 2;
            } else if (a == 1 || b == 1) {
                res = 1;
            } else {
                res = 0;
            }
        }

        // curは閉じ括弧に位置する
        ++cur;
        return res;
    } else if (S[cur] == '-') {  // S[cur] == '-'
        int a = eval(S, ++cur);
        return 2 - a;
    } else if (S[cur] == 'P') {
        ++cur;
        return P;
    } else if (S[cur] == 'Q') {
        ++cur;
        return Q;
    } else if (S[cur] == 'R') {
        ++cur;
        return R;
    } else {
        int res = (int)(S[cur] - '0');
        ++cur;
        return res;
    }
}

int main() {
    string S;
    while (cin >> S, S != ".") {
        int res = 0;
        for (P = 0; P <= 2; ++P) {
            for (Q = 0; Q <= 2; ++Q) {
                for (R = 0; R <= 2; ++R) {
                    int cur = 0;
                    if (eval(S, cur) == 2) ++res;
                    //cout << "cur: " << cur << endl;
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}