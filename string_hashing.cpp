// https://codeforces.com/contest/633/problem/C

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define sz(x) (int)(x.size())
#define FOR(i,L,R) for(int i = L; i <= R; i++)

const int N = 1e5 + 5, prime = 91, mod = 1e9 + 7;

struct HASH // template credits : ashishgup
{
    vector<int> hashs;
    vector<int> pows;
    int P;
    int MOD;

    HASH() {}

    HASH(string &s, int P, int MOD) : P(P), MOD(MOD) 
    {
        int n = s.size();
        pows.resize(n + 1, 0);
        hashs.resize(n + 1, 0);
        pows[0] = 1;
        for(int i = n - 1; i >= 0; i--) 
        {
            hashs[i] = (1LL * hashs[i + 1] * P + s[i] - 'a' + 1) % MOD;
            pows[n - i] = (1LL * pows[n - i - 1] * P) % MOD;
        }
        pows[n] = (1LL * pows[n - 1] * P) % MOD;
    }

    int get_hash(int l, int r) 
    {
        int ans = hashs[l] + MOD - (1LL * hashs[r + 1] * pows[r - l + 1]) % MOD;
        ans %= MOD;
        return ans;
    }
} S;

int n, m;
string s, t[N];
vector<int> lens;
map<int,string> info;
set<int> available_hashes;
int dp[N];

int go(int from) {
    if (from == n)
        return 1;

    int &ans = dp[from];
    if (~ans)
        return ans;

    ans = 0;

    for (int len : lens) if (from + len - 1 < n) {
        int want_hash = S.get_hash(from, from + len - 1);
        if (available_hashes.count(want_hash)) {
            ans |= go(from + len);
        }
    }

    return ans;
}

void trace(int from) {
    if (from == n)
        return ;

    for (int len : lens) if (from + len - 1 < n) {
        int want_hash = S.get_hash(from, from + len - 1);
        if (go(from + len) && available_hashes.count(want_hash)) {
            cout << info[want_hash] << ' ';
            return trace(from + len);
        }
    }

}

int32_t main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> s >> m;

    memset(dp, -1, sizeof(dp));
    S = HASH(s, prime, mod);

    set<int> lengths;

    FOR(i,1,m) {
        cin >> t[i];
        string curr = t[i];
        reverse(curr.begin(), curr.end());

        for(char &ch : curr) 
            ch = tolower(ch);

        int curr_hash = HASH(curr, prime, mod).get_hash(0, sz(curr) - 1);
        info[curr_hash] = t[i];
        lengths.insert(sz(curr));
        available_hashes.insert(curr_hash);
    }

    for(int len : lengths) {
        lens.push_back(len);
    }

    bool found = go(0);
    assert(found);
    trace(0);
}

