 
const int N = 1200005;

class TRIE{

	private:
      vector<vector<int>> adj;
      vector<int> cnt, endNode;
		int nodeId;

	public:
		TRIE(){
			for(int i = 0; i < N; i++){
	            vector<int> add(3, -1);
	            adj.push_back(add);
	            cnt.push_back(0);
	            endNode.push_back(0);
         	}
			nodeId = 1;
		}

		void insert(string &s){
			int v = 0;
			for(int i = 0; i < sz(s); i++){
				int curr = s[i] - 'a';
				if(adj[v][curr] == -1)
					adj[v][curr] = nodeId++;
				v = adj[v][curr];
				cnt[v]++;
			}
			endNode[v] = 1;
		}

		bool search(string &s){
			int v=0;
			for(int i = 0; i < sz(s); i++){
				int cur = s[i] - 'a';
				if(adj[v][cur] == -1)
					return 0;
				v = adj[v][cur];
			}
			return endNode[v];
		}

		int check(string &str, int i = 0, int v = 0, int cnt = 0){    //this function wrt to Problem : https://codeforces.com/contest/514/problem/C
			if(cnt > 1) return 0;
			if(i == sz(str))
				return (cnt == 1 && endNode[v]);
			int currCheck = 0;
			int cur = str[i]-'a';
			for(int j=0;j<=2;j++){
				if(adj[v][j]==-1)
					continue;
					currCheck |= check(str, i+1, adj[v][j], cnt + (j != cur));
			}
			return currCheck;
		}
	
};
