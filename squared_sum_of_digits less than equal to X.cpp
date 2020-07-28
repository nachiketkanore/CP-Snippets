#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)(x.size())
#define FOR(x,y,z) for(int x = y; x <= z; x++)
#define int long long

const int N = 1e5 + 2, inf = 1e18;

void generate(int x) {
    std::vector<int> data;
    const int MAX_SIZE = 500002;
    const int mod = 998244353;

    queue<pair<int,int>> Q;
    // first = actual number modded, second = squared sum of its digits
    FOR(dig,1,9) {
        if(dig * dig <= x) {
            Q.push({dig, dig * dig});
            data.push_back(dig);
        }
    }
    while(!Q.empty())
    {
        if(sz(data) > MAX_SIZE) break;
        auto curr = Q.front();
        Q.pop();

        int val_mod = curr.first;
        int squared_sum_of_digits = curr.second;

        FOR(dig,0,9)
        {
            int next_val_mod = (val_mod * 10 + dig) % mod;
            int next_squared_sum_of_digits = squared_sum_of_digits + dig*dig;

            if(next_squared_sum_of_digits <= x) {
                data.push_back(next_val_mod);
                Q.push({next_val_mod, next_squared_sum_of_digits});
            }
        }
    }

    // Data[i] has the i-th beautiful number
    for(int x : data) {
        cout << x << '\n';
    }
}

/*

1. There are infinite numbers with squared_sum_of_digits <= X

2. We just need first 500K numbers, and the squared_sum_of_digits 
    wont increase much

3. The 10^10 constraint on X is kind of useless.
    The upper bound is quite low actually

4. Notice when X = 10^10 or some big number, first 500K natural numbers would suffice

5. Main problem is generating numbers when X is quite low (like < 200 or so)

Problems on similar concepts:
https://www.spoj.com/problems/MULTII/
https://codeforces.com/contest/1070/problem/A

*/

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);  
    
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif

    int x;
    cin >> x;
    generate(x);
}
