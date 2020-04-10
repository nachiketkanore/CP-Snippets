Problem : https://codeforces.com/contest/858/problem/D

/*
  ______    _ _ ____       _   _            _   _           _ _______ _                
 |  ____|  (_) |  _ \     | | | |          | \ | |         | |__   __(_)               
 | |__ __ _ _| | |_) | ___| |_| |_ ___ _ __|  \| | _____  _| |_ | |   _ _ __ ___   ___ 
 |  __/ _` | | |  _ < / _ \ __| __/ _ \ '__| . ` |/ _ \ \/ / __|| |  | | '_ ` _ \ / _ \
 | | | (_| | | | |_) |  __/ |_| ||  __/ |  | |\  |  __/>  <| |_ | |  | | | | | | |  __/
 |_|  \__,_|_|_|____/ \___|\__|\__\___|_|  |_| \_|\___/_/\_\\__||_|  |_|_| |_| |_|\___|
                                                                                       
                                                                                       
*/
#include <bits/stdc++.h>
#define int long long
#define sz(x) (int)(x.size())
using namespace std;

class node{
   public:
      node* child[10];
      int cnt;
      node(){
         for(int i = 0; i < 10; i++)
            child[i] = NULL;
         cnt = 0;
      }
};

typedef node* nodeptr;

class TRIE{
   private:
      nodeptr root;

   public:

      TRIE(){
         root = new node();
      }

      void insert(string &s){
         int n = sz(s);
         nodeptr curr = root;
         for(int i = 0; i < n; i++){
            int next = s[i] - '0';
            if(curr->child[next] == NULL)
               curr->child[next] = new node();
            curr = curr->child[next];
            
         }
         curr->cnt++;
      }

      int getCount(string &s){
         nodeptr curr = root;
         for(int i = 0; i < sz(s); i++){
            int next = s[i] - '0';
            if(curr->child[next] == NULL)
               return 0;
            curr = curr->child[next];
         }
         return curr->cnt;
      }

};
 
set<string> f[70000];

int32_t main(){

	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

   int n;
   cin >> n;
   TRIE T;

   for(int i = 0; i < n; i++){
      string s;   cin >> s;
      for(int j = 0; j < sz(s); j++){
         string curr;
         for(int k = j; k < sz(s); k++){
            curr += s[k];
            f[i].insert(curr);
         }
      }
      for(string it : f[i])
         T.insert(it);
   }

   for(int i = 0; i < n; i++){
      string ans = "99999999999";
      for(string it : f[i]){
         int cnt = T.getCount(it);
         if(cnt == 1 && (sz(ans) > sz(it)))
            ans = it;
      }
      cout << ans << '\n';
   }
	
	return 0;
} 
