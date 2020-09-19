#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define repeat(i, n) for (int i = 0; (i) < (n); ++(i))
#define repeat_from(i, m, n) for (int i = (m); (i) < (n); ++(i))
using namespace std;
template <class T>
void setmax(T &a, T const &b) {
    if (a < b) a = b;
}

template <class T>
void setmin(T &a, T const &b) {
    if (a > b) a = b;
}

template <typename T, typename X>
auto vectors(T a, X x) { return vector<T>(x, a); }

template <typename T, typename X, typename Y, typename... Zs>
auto vectors(T a, X x, Y y, Zs... zs) {
    auto cont = vectors(a, y, zs...);
    return vector<decltype(cont)>(x, cont);
}

const int udeg = 1125;
const int degtbl[] = {udeg, udeg * 3, udeg * 5, udeg * 7, udeg * 9, udeg * 11, udeg * 13, udeg * 15, udeg * 17, udeg * 19, udeg * 21, udeg * 23, udeg * 25, udeg * 27, udeg * 29, udeg * 31};
const char dirtbl[][4] = {"NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW", "N"};
const int windtbl[][2] = {{0, 5 * 3}, {5 * 3, 31 * 3}, {31 * 3, 67 * 3}, {67 * 3, 109 * 3}, {109 * 3, 159 * 3}, {159 * 3, 215 * 3}, {215 * 3, 277 * 3}, {277 * 3, 343 * 3}, {343 * 3, 415 * 3}, {415 * 3, 489 * 3}, {489 * 3, 569 * 3}, {569 * 3, 653 * 3}, {653 * 3, 100000000}};

int main() {
    int deg, dis;
    cin >> deg >> dis;
    deg *= 10;

    int n = sizeof(degtbl) / sizeof(degtbl[0]);
    int x = 0, y = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (degtbl[i] <= deg && deg < degtbl[(i + 1) % n]) {
            x = i;
            break;
        }
    }
    if (degtbl[n - 1] <= deg || deg < degtbl[0]) {
        x = n - 1;
    }

    n = sizeof(windtbl) / sizeof(windtbl[0]);
    for (int i = 0; i < n; ++i) {
        if (windtbl[i][0] <= dis && dis < windtbl[i][1]) {
            y = i;
            break;
        }
    }

    if (y == 0) {
        cout << "C 0" << endl;
    } else {
        cout << dirtbl[x] << " " << y << endl;
    }
    return 0;
}