#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

const int N = 1e6, inf = 1e18, mod = 1e9 + 7;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int files = 5;
    for(int i = 0; i < files; i++){
        string in_file_name = "input" + to_string(i) + ".txt";
        string out_file_name = "output" + to_string(i) + ".txt";

        const char* inp = in_file_name.data();
        const char* out = out_file_name.data();

        #ifndef ONLINE_JUDGE
        freopen(inp,"r",stdin);
        freopen(out,"w",stdout);
        #endif

        int n, sum = 0;
        cin >> n;
        for(int i = 0, u; i < n; i++)
            cin >> u, sum += u;
        cout << "Sum = " << sum << endl;
    }
}