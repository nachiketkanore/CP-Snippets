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

    int n;  cin >> n;

    cache[1] = 1;
    cache[2] = 2;

    for(int x=1;x<=n;x++){
        cout << fibo(x) << endl;
    }

    cout << "Called = " << called << endl;

    return 0;
}
