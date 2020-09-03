#include <iostream>
#include <string>
#include <tuple>
using namespace std;

int main() {
    string Era;
    int y, m, d;
    tuple<int, int, int> Criteria = make_tuple(31, 5, 1);
    while (cin >> Era >> y >> m >> d, Era != "#") {
        tuple<int, int, int> date = make_tuple(y, m, d);
        if (date < Criteria) {
            cout << "HEISEI"
                 << " "
                 << y << " " << m << " " << d << endl;
        } else {
            cout << "? " << y - 30 << " " << m << " " << d << endl;
        }
    }
    return 0;
}