int nCr(int n, int r){
    int p = 1, k = 1;
    r = min(r, n - r);
    if(r != 0){
        while(r){
            p *= n;
            k *= r;
            int g = __gcd(p,k);
            p /= g;
            k /= g;
            n--, r--;
        }
    }else p = 1;
    return p;
}
