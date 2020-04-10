
class segTree{

   private:
      int n;
      vector<int> st,arr;
   public:
      //Keeping it 1-based
      void init(int _n){
         n = _n;
         st = vi(4 * n + 5);
         arr = vi(n+1);
         for(int i = 1; i <= n; i++){
            cin >> arr[i];
         }
         build(1, 1, n);
      }

      void build(int node, int tl, int tr){
         if(tl == tr)
            st[node] = arr[tl];
         else{
            int mid = (tl + tr)/2;
            build(2 * node, tl, mid);
            build(2 * node +1, mid + 1, tr);
            st[node] = min(st[2 * node], st[2 * node + 1]);
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
            st[node] = min(st[2 * node], st[2 * node + 1]);
         }

      }

      int rangeQuery(int node, int tl, int tr, int l, int r){
         if(l > r) return inf;
         if((l == tl) && (r == tr))
            return st[node];
         int mid = (tl + tr) / 2;
         int left_ans = rangeQuery(2*node, tl , mid, l, min(r,mid));
         int right_ans = rangeQuery(2*node + 1, mid + 1, tr, max(l, mid + 1), r);
         return min(left_ans, right_ans);
      }

      void update(int pos, int val){
         pointUpdate(1, 1, n, pos, val);
      }

      int query(int l, int r){
         return rangeQuery(1, 1, n, l, r);
      }

} T;
