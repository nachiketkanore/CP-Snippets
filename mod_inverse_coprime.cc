
int gcdExtended(int a, int b, int* x, int* y) {  
    if (a == 0) { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1); 

    *x = y1 - (b / a) * x1; 
    *y = x1; 
  
    return gcd; 
} 

// (1/a) % m when (a and m are coprime)
int modInverse(int a, int m) { 
	assert(__gcd(a, m) == 1);
    int x, y; 
    int g = gcdExtended(a, m, &x, &y); 
    if (g != 1) 
        assert(false);
    else { 
        int res = (x % m + m) % m; 
        return res;
    } 
} 
