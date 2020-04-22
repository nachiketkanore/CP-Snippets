#include "bits/stdc++.h"
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

const int N = 1e6, inf = 1e18, mod = 1e9 + 7;

int32_t main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);  

    // #ifndef ONLINE_JUDGE
    // freopen("input.txt","r",stdin);
    // freopen("out.txt","w",stdout);
    // #endif
    srand(time(NULL));

    int files = 5;
    for(int i = 0; i < files; i++){
    	string file_name = "input" + to_string(i) + ".txt";
        
        /* Just for creating blank files
        std::ofstream myfile { file_name };
        myfile.close();
        */

        ofstream myfile (file_name);
          if (myfile.is_open())
          {
            int n = 1 + rand() % 10;
            myfile << n << endl;
            for(int j = 0; j < n; j++)
                myfile << (1 + rand() % n) << " ";
            myfile.close();
          }
          else cout << "Unable to open file";
    }
}