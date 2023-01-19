#include <bits/stdc++.h>
using namespace std;

#define IOS                                                                    \
  ios::sync_with_stdio(0);                                                     \
  cin.tie(0);                                                                  \
  cout.tie(0);
#define endl "\n"
#define int long long

class TRIE {
private:
  typedef struct data {
    data *bit[2];
    int cnt = 0;
  } trie;

  trie *head;

public:
  TRIE() { // constructor
    head = new trie();
  }

  void insert(int x) {
    trie *node = head;
    for (int i = 30; i >= 0; i--) {
      int curbit = (x >> i) & 1;
      if (node->bit[curbit] == NULL) {
        node->bit[curbit] = new trie();
      }
      node = node->bit[curbit];
      node->cnt++;
    }
  }

  void remove(int x) {
    trie *node = head;
    for (int i = 30; i >= 0; i--) {
      int curbit = (x >> i) & 1;
      node = node->bit[curbit];
      node->cnt--;
    }
  }

  int maxxor(int x) {
    trie *node = head;
    int ans = 0;
    for (int i = 30; i >= 0; i--) {
      int curbit = (x >> i) & 1;
      if (node->bit[curbit ^ 1] != NULL && node->bit[curbit ^ 1]->cnt > 0) {
        ans += (1LL << i);
        node = node->bit[curbit ^ 1];
      } else
        node = node->bit[curbit];
    }
    return ans;
  }
};

int32_t main() {
  IOS;
  TRIE T;

  T.insert(0);
  int q;
  cin >> q;
  while (q--) {
    char ch;
    cin >> ch;
    int x;
    cin >> x;
    if (ch == '+')
      T.insert(x);
    else if (ch == '-')
      T.remove(x);
    else
      cout << T.maxxor(x) << endl;
  }
  return 0;
}
