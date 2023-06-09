#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define mt make_tuple
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

template<class T> bool uin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool uax(T &a, T b) { return a < b ? (a = b, true) : false; }

const int maxn = 210000;
vi teams[maxn], same[maxn];

bool emulate(int x, int y) {
    int xi = teams[x].size() - 1, yi = teams[y].size() - 1;
    while (xi >= 0 && yi >= 0) {
        int skip = min((same[x][xi] - 1) / teams[y][yi], (same[y][yi] - 1) / teams[x][xi]);
        uax(skip, 0);
        xi -= skip * teams[y][yi];
        yi -= skip * teams[x][xi];
        
        yi -= teams[x][xi];
        if (yi < 0) break;
        xi -= teams[y][yi];
    }
    return xi >= 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#endif

    int n, k, q;
    cin >> n >> k >> q;
    forn(i, n) {
        int s, t;
        cin >> s >> t;
        teams[--t].pb(s);
    }
    forn(i, k) {
        sort(all(teams[i]));
        same[i].pb(0);
        for1(j, teams[i].size() - 1) {
            if (teams[i][j] != teams[i][j - 1]) same[i].pb(1);
            else same[i].pb(same[i][j - 1] + 1);
        }
    }
    forn(i, q) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, id;
            cin >> p >> id;
            --id;
            if (!teams[id].empty() && p == teams[id].back()) same[id].pb(same[id][same[id].size() - 1] + 1);
            else same[id].pb(1);
            teams[id].pb(p);
        } else {
            int x, y;
            cin >> x >> y;
            --x; --y;
            cout << (emulate(x, y) ? x : y) + 1 << '\n';
        }
    }

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
