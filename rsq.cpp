
class segTree{

   private:
      int n;
      vector<int> st;
   public:
      //Keeping it 1-based
      void init(int _n){
         n = _n;
         st.resize(4*n + 5,0LL);
         build(1, 1, n);
      }

      void build(int node, int tl , int tr){
         if(tl == tr)
            st[node] = 0;
         else{
            int tm = (tl + tr)/2;
            build(2 * node, tl, tm);
            build(2 * node + 1, tm + 1, tr);
            st[node] = st[2*node] + st[2*node + 1];
         }
      }

      void pointUpdate(int node, int tl, int tr, int pos, int val){
         if(tl == tr){
            st[node] = val;
         }else{
            int mid = (tl + tr)/2;
            if(pos <= mid)
               pointUpdate(2*node, tl, mid, pos, val);
            else
               pointUpdate(2*node + 1, mid + 1, tr, pos, val);
            st[node] = st[2 * node] + st[2 * node + 1];
         }

      }

      int rangeQuery(int node, int tl, int tr, int l, int r){
         if(l > r) return 0;
         if((l == tl) && (r == tr))
            return st[node];
         int mid = (tl + tr) / 2;
         int left_ans = rangeQuery(2*node, tl , mid, l, min(r,mid));
         int right_ans = rangeQuery(2*node + 1, mid + 1, tr, max(l, mid + 1), r);
         return left_ans + right_ans;
      }

      void update(int pos, int val){
         pointUpdate(1, 1, n, pos, val);
      }

      int query(int l, int r){
         return rangeQuery(1, 1, n, l, r);
      }

} T;
