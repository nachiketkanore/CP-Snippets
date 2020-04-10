class Solution {
public:
    const int N = 1e3 + 5;
    int dp[1005][1005];
    
    int go(int l, int r, string &s){
        if(l >= r)
            return 1;
        int &ans = dp[l][r];
        if(ans != -1)
            return ans;
        ans = 0;
        if(s[l] == s[r])
            ans = go(l+1, r-1,s);
        return ans;
    }
    
    int countSubstrings(string s) {
        memset(dp, -1, sizeof(dp));
        int ans = 0;
        int n = s.size();
        for(int i = 0; i < n; i++)
            for(int j = i; j < n; j++)
                ans += go(i,j,s);
        return ans;
    }
};
