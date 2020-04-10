// Author : Nachiket Kanore
// Institute : PICT, Pune

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <random>
#include <cmath>
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <complex>
#include <numeric>
#include <limits>
#include <bitset>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <map>
#include <set>

using namespace std;

#define int long long
#define endl '\n'
#define rep(x,s,e) for(int x=s;x<=(e);x++)
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(), x.rend()
#define precise(x) cout << fixed << setprecision(x)
#define pb push_back
#define mp make_pair
#define test int t; cin>>t; while(t--)
#define FAST                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
 
 
typedef vector<int> vi;
typedef vector<pair<int,int>> vii;
typedef pair<int,int> pii;
 
const int mod = 1e9+7;
const int inf = 1e18;
const int N = 2e5+10;

int cache[N];

int called;

int fibo(int n){
    if(cache[n])
        return cache[n];

    called++;
    int nth = fibo(n-1) + fibo(n-2); //Top-Down with memoization
    cache[n] = nth;
    return cache[n];
    //return fibo(n-1) + fibo(n-2); //Recursive
}

int32_t main(){
    FAST;

    int n;  cin >> n;

    cache[1] = 1;
    cache[2] = 2;

    for(int x=1;x<=n;x++){
        cout << fibo(x) << endl;
    }

    cout << "Called = " << called << endl;

    return 0;
}
