//Problem : https://codeforces.com/problemset/problem/1326/D2

#include <bits/stdc++.h>
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

const int N = 1e5 + 1, M = 5e3 + 5, inf = 1e18, mod = 1e9 + 7;

string Manacher(string s){
    int n = sz(s);

    vector<int> d1(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
            k++;
        }
        d1[i] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }

    vector<int> d2(n);
    for (int i = 0, l = 0, r = -1; i < n; i++) {
        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
            k++;
        }
        d2[i] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }

    int maxLen = 1;
    for(int i = 0; i < n; i++){
        if(d1[i] == i+1)
            maxLen = max(maxLen, 2*i+1);
        if(d2[i] == i)
            maxLen = max(maxLen, 2*i);
    }
    return s.substr(0,maxLen);
}

string findBest(int l, int r, string S){
    string s = S.substr(l,r - l + 1);
    string bestPref = Manacher(s);
    reverse(s.begin(), s.end());
    string bestSuff = Manacher(s);
    return (sz(bestPref) > sz(bestSuff) ? bestPref : bestSuff);
}

void solve(){
    string s;
    cin >> s;
    int n = sz(s);
    int l = 0, r = n -1;
    while(l < r && s[l] == s[r])    l++, r--;
    if(l >= r){
        cout << s << '\n';
        return;
    }
    string ans = s.substr(0,l) + findBest(l,r,s) + s.substr(r+1);
    cout << ans << '\n';
}

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);	

    int t;
    cin >> t;
    while(t--)
        solve();
}
