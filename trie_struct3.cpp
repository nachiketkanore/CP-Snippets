
class Trie {
private:
  vector<Trie *> children;
  bool this_inserted = false;

public:
  /** Initialize your data structure here. */
  Trie() {
    children.resize(26, NULL);
    this_inserted = false;
  }

  /** Inserts a word into the trie. */
  void insert(string word) {
    Trie *cur = this;

    for (char c : word) {
      int ind = c - 'a';
      if (cur->children[ind] == NULL) {
        cur->children[ind] = new Trie();
      }
      cur = cur->children[ind];
    }

    cur->this_inserted = true;
  }

  /** Returns if the word is in the trie. */
  bool search(string word) {
    Trie *cur = this;

    for (char c : word) {
      int ind = c - 'a';
      if (cur->children[ind] == NULL) {
        return false;
      }
      cur = cur->children[ind];
    }

    return cur->this_inserted;
  }

  /** Returns if there is any word in the trie that starts with the given
   * prefix. */
  bool startsWith(string prefix) {
    string word = prefix;

    Trie *cur = this;

    for (char c : word) {
      int ind = c - 'a';
      if (cur->children[ind] == NULL) {
        return false;
      }
      cur = cur->children[ind];
    }

    return true;
  }
};
