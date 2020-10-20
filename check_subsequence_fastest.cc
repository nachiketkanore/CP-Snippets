// https://binarysearch.com/problems/Subsequence-Match-Target

#include "solution.hpp"
using namespace std;

class Solution {
    public:
    string S;
    int n;
    vector<int> ids[30];
    
    bool is(string &one) {
        if (n < one.size()) return false;
        
        int from = 0;
        
        for (char ch : one) {
            int lo = 0, hi = ids[ch - 'a'].size() - 1;
            int nxt = -1;
            
            while (lo <= hi) {
                int mid = (lo + hi) >> 1;
                if (ids[ch - 'a'][mid] >= from) {
                    nxt = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            
            if (~nxt) {
                from = ids[ch - 'a'][nxt] + 1;
            } else return false;
        }
        
        return true;
    }
    int solve(vector<string>& words, string s) {
        int ans = 0;
        S = s;
        n = s.size();
        
        for (int i = 0; i < n; i++) {
            ids[s[i] - 'a'].push_back(i);
        }
        
        for (auto &it : words) {
            ans += is(it);
        }
        return ans;
    }
};
