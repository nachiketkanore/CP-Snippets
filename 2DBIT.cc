struct BIT2D { 
    int bit[SZ+1][SZ+1];
    void upd(int X, int Y, int val) {
        for (; X <= SZ; X += (X&-X))
            for (int Y1 = Y; Y1 <= SZ; Y1 += (Y1&-Y1))
                bit[X][Y1] += val;
    }
    int query(int X, int Y) {
        int ans = 0;
        for (; X > 0; X -= (X&-X))
            for (int Y1 = Y; Y1 > 0; Y1 -= (Y1&-Y1))
                ans += bit[X][Y1];
        return ans;
    }
    int getSum(int R1, int R2, int C1, int C2) {
    	int X1 = min(R1, R2);
    	int Y1 = min(C1, C2);
    	int X2 = max(R1, R2);
    	int Y2 = max(C1, C2);
    	assert(X1 <= X2 && Y1 <= Y2);
    	int ans = query(X2, Y2) - query(X2, Y1-1) - query(X1-1, Y2) + query(X1-1,Y1-1);
    	return ans;
    }
} bit;
