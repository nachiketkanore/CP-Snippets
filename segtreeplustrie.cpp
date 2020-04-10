Problem : https://www.codechef.com/problems/MCO16404
Partial solution : 

/*
    __  __               __                    __      __               __          ______      __           __ 
   / / / /___ __________/ /      ______  _____/ /__   / /_  ___  ____ _/ /______   /_  __/___ _/ /__  ____  / /_
  / /_/ / __ `/ ___/ __  / | /| / / __ \/ ___/ //_/  / __ \/ _ \/ __ `/ __/ ___/    / / / __ `/ / _ \/ __ \/ __/
 / __  / /_/ / /  / /_/ /| |/ |/ / /_/ / /  / ,<    / /_/ /  __/ /_/ / /_(__  )    / / / /_/ / /  __/ / / / /_  
/_/ /_/\__,_/_/   \__,_/ |__/|__/\____/_/  /_/|_|  /_.___/\___/\__,_/\__/____/    /_/  \__,_/_/\___/_/ /_/\__/  
                                                                                                                
*/
#include <bits/stdc++.h>

using namespace std;

#define int long long
const int inf = 1e18, N = 3e5 + 1;

typedef struct node{
   node* edge[2];
}* nodeptr;


struct TRIE{
  
   nodeptr root = new node();

   void insert(int val){
      nodeptr curr = root;
      for(int i = 22; i >= 0; i--){
         int bx = (val >> i) & 1;
         if(curr->edge[bx] == NULL)
            curr->edge[bx] = new node();
         curr = curr->edge[bx];
      }
   }

   int query(int val){
      nodeptr curr = root;
      int ans = 0;
      for(int i = 22; i >= 0; i--){
         int bx = (val >> i) & 1;
         if(curr->edge[bx ^ 1] != NULL){
            ans += (1LL << i);
            curr = curr->edge[bx ^ 1];
         }else 
            curr = curr->edge[bx];
      }
      return ans;
   }
};

struct segTree{
   TRIE tree[4 * N];

   void update(int id, int tl, int tr, int ind, int &val){

      if(ind > tr || ind < tl) return;
      if(tl == tr)
         tree[id].insert(val);
      else{
         tree[id].insert(val);
         int mid = (tl + tr) / 2;
         update(2*id + 1 ,tl , mid , ind, val);
         update(2*id + 2, mid + 1, tr, ind ,val);
          //Merge function remaining
      }
   }

   int query(int id, int tl, int tr, int ql , int qr, int &val){
      if(ql > tr || qr < tl)
         return 0;
      if(ql <= tl and qr >= tr)
         return tree[id].query(val);
      int mid = (tl + tr)/ 2;
      int ans1 = query(2*id + 1, tl , mid, ql , qr ,val);
      int ans2 = query(2*id + 2, mid + 1, tr, ql , qr, val);
      return max(ans1, ans2);
   }

};

segTree ST;

int32_t main(){ 
   ios::sync_with_stdio(false);
   cin.tie(NULL); cout.tie(NULL);

   int n ;  cin >> n;
   for(int i = 0; i < n; i++){
      int val; cin >> val;
      ST.update(0, 0 , N, i, val);
   }
   int q;   cin >> q;
   while(q--){
      int l , r, k;
      cin >> l >> r >> k;
      cout << ST.query(0, 0 , N , l-1, r-1, k) << '\n';
   }
   
}

