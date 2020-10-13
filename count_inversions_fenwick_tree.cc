struct FenwickTree {
        vector<int> bit;  // binary indexed tree
        int n;
     
        FenwickTree(int n) {
            this->n = n;
            bit.assign(n, 0);
        }
     
        FenwickTree(vector<int> a) : FenwickTree(a.size()) {
            for (size_t i = 0; i < a.size(); i++)
                add(i, a[i]);
        }
     
        int sum(int r) {
            int ret = 0;
            for (; r >= 0; r = (r & (r + 1)) - 1)
                ret += bit[r];
            return ret;
        }
     
        int sum(int l, int r) {
            return sum(r) - sum(l - 1);
        }
     
        void add(int idx, int delta) {
            for (; idx < n; idx = idx | (idx + 1))
                bit[idx] += delta;
        }
    };
    
    void compress(vector<int> &a) {
        vector<int> vals = a;
        sort(vals.begin(), vals.end());
        for (int &x : a) {
            x = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
        }
    }
     
    int inversions(vector<int> &a) {
    	const int n = a.size();
        compress(a);
    	FenwickTree tree(n + 5);
     
    	int ans = 0;
     
    	for (int x : a) {
    		int from = x + 1, to = n;
    		ans += tree.sum(from, to);
    		tree.add(x, 1);
    	}
    	return ans;
    }
