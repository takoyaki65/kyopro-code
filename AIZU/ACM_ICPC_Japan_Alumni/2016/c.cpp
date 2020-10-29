#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    node *lch;
    node *rch;
};

node *Tree(int &cur, string &S);
node *Node(int &cur, string &S);
int Val(int &cur, string &S);

node *Tree(int &cur, string &S) {
    assert(S[cur] == '(');
    ++cur;  // (
    node *lch = Node(cur, S);
    assert(S[cur] == ')');
    ++cur;  // )
    assert(S[cur] == '[');
    ++cur;  // [
    int val = Val(cur, S);
    assert(S[cur] == ']');
    ++cur;  // ]
    assert(S[cur] == '(');
    ++cur;  // (
    node *rch = Node(cur, S);
    ++cur;  // )
    node *ret = new node;
    ret->lch = lch;
    ret->val = val;
    ret->rch = rch;
    return ret;
}

node *Node(int &cur, string &S) {
    if (S[cur] == ')') {
        return NULL;
    }
    return Tree(cur, S);
}

int Val(int &cur, string &S) {
    int ret = 0;
    assert(isdigit(S[cur]));
    while (isdigit(S[cur])) {
        ret *= 10;
        ret += S[cur] - '0';
        ++cur;
    }
    return ret;
}

string Tree2String(node *tree) {
    string ret = "";
    if (tree == NULL) return ret;
    ret += "(";
    ret += Tree2String(tree->lch);
    ret += ")[";
    ret += to_string(tree->val);
    ret += "](";
    ret += Tree2String(tree->rch);
    ret += ")";
    return ret;
}

node *UniteTree(node *A, node *B) {
    if (A == NULL or B == NULL) return NULL;
    node *ret = new node;
    ret->val = A->val + B->val;
    ret->lch = UniteTree(A->lch, B->lch);
    ret->rch = UniteTree(A->rch, B->rch);
    return ret;
}

int main() {
    string A, B;
    cin >> A >> B;
    int curA = 0, curB = 0;
    node *TreeA = Tree(curA, A);
    node *TreeB = Tree(curB, B);
    //cout << "string2Tree done" << endl;
    node *TreeAB = UniteTree(TreeA, TreeB);
    cout << Tree2String(TreeAB) << endl;
    return 0;
}