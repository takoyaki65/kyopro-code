#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    int ac(0), wa(0), tle(0), re(0);
    string S;
    while (N--) {
        cin >> S;
        if (S == "AC")
            ++ac;
        else if (S == "TLE")
            ++tle;
        else if (S == "WA")
            ++wa;
        else if (S == "RE")
            ++re;
        else
            ;
    }
    cout << "AC x " << ac << endl;
    cout << "WA x " << wa << endl;
    cout << "TLE x " << tle << endl;
    cout << "RE x " << re << endl;
    return 0;
}
