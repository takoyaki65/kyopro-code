//http://dai1741.github.io/maximum-algo-2012/docs/parsing/
#include <bits/stdc++.h>
using namespace std;

/*
<expr>      ::= <term> [ ('+'|'-') <term> ]*
<term>      ::= <factor> [ ('*'|'/') <factor> ]*
<factor>    ::= <number> | '(' <expr> ')'
<number>    ::= 1つ以上の数字
注: [...]*という表記は，括弧内のものが0回以上繰り返されることを意味する．
*/

// @pram s: 今読み込んでいる式
// @param i: 式中の位置
int expr(string& s, int& i);
int term(string& s, int& i);
int factor(string& s, int& i);
int number(string& s, int& i);

int expr(string& s, int& i) {
    int val = term(s, i);
    while (s[i] == '+' || s[i] == '-') {
        char op = s[i];
        i++;
        int val2 = term(s, i);
        if (op == '+')
            val += val2;
        else
            val -= val2;
    }
    return val;
}

int term(string& s, int& i) {
    int val = factor(s, i);
    while (s[i] == '*' || s[i] == '/') {
        char op = s[i];
        i++;
        int val2 = factor(s, i);
        if (op == '*')
            val *= val2;
        else
            val /= val2;
    }
    return val;
}

int factor(string& s, int& i) {
    if (isdigit(s[i])) return number(s, i);

    // ここで構文が正しければs[i] == '('となる
    i++;
    int ret = expr(s, i);
    i++;  // ')'を読み飛ばす
    return ret;
}

int number(string& s, int& i) {
    int val = s[i] - '0';
    while (isdigit(s[++i])) {
        val *= 10;
        val += s[i] - '0';
    }
    return val;
    /*
    int n = s[i++] - '0';
    while(isdigit(s[i])) n = n*10 + s[i++] - '0';
    return n;
    */
}

int main() {
    string str;
    cin >> str;
    int i = 0;
    cout << str << " = " << expr(str, i) << endl;
    return 0;
}