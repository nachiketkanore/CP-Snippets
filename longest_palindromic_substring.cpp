// Tested on : https://leetcode.com/problems/longest-palindromic-substring

class Solution {
public:
  const int N = 1e3 + 5;
  int dp[1003][1003];

  int go(int l, int r, string &s) {
    if (l >= r)
      return 1;
    int &ans = dp[l][r];
    if (ans != -1)
      return ans;
    ans = 0;
    if (s[l] == s[r])
      ans = go(l + 1, r - 1, s);
    return ans;
  }

  string longestPalindrome(string s) {
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    int n = s.size();
    if (n == 0)
      return "";
    int l = -1, r = -1;
    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++) {
        if (go(i, j, s) && ans < (j - i + 1)) {
          ans = j - i + 1;
          l = i, r = j;
        }
      }
    return s.substr(l, ans);
  }
};
