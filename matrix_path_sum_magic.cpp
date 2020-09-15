// https://www.hackerearth.com/practice/algorithms/dynamic-programming/2-dimensional/practice-problems/algorithm/help-him-9659b063/description/
const int N = 1003;
int dp[N][N];

int32_t main(){
    FAST;

    int n;  cin >> n;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            cin >> dp[i][j];
            if(i == 1)  dp[i][j] += dp[i][j-1];
            else if(j == 1)  dp[i][j] += dp[i-1][j];
            else{
                dp[i][j] = min(dp[i-1][j] + dp[i][j] , dp[i][j-1] + dp[i][j]);
            }
        }
    }

    cout << dp[n][n] << endl;

    return 0;
}

