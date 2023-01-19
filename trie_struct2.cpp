struct Trie {
  // These are freed when the Trie is destroyed.
  vector<unique_ptr<Trie>> children = vector<unique_ptr<Trie>>(26);
  bool word = false;

  template <typename It> void insert(It begin, It end) {
    if (begin == end) {
      word = true;
      return;
    }
    const size_t index = (*begin) - 'a';
    if (!children[index]) {
      // This is better, but only C++14.
      // children[index] = make_unique<Trie>();
      children[index].reset(new Trie());
    }
    children[index]->insert(begin + 1, end);
  }

  template <typename It> bool contains(It begin, It end) const {
    if (begin == end) {
      return word;
    }
    const size_t index = (*begin) - 'a';
    if (!children[index]) {
      return false;
    }
    return children[index]->contains(begin + 1, end);
  }

  // 0 - Does not.
  // 1 - This is the prefix of something.
  // 2 - Full match.
  template <typename It> int contains_as_prefix(It begin, It end) const {
    if (begin == end) {
      if (word) {
        return 2;
      } else {
        return 1;
      }
    }
    const size_t index = (*begin) - 'a';
    if (!children[index]) {
      return 0;
    }
    return children[index]->contains_as_prefix(begin + 1, end);
  }

  i64 words() const {
    i64 words = 0;
    if (word) {
      words++;
    }
    for (const unique_ptr<Trie> &child : children) {
      if (child) {
        words += child->words();
      }
    }
    return words;
  }

  int children_count() const {
    int count = 0;
    for (const unique_ptr<Trie> &child : children) {
      if (child) {
        count++;
      }
    }
    return count;
  }

  void branch_count(unordered_map<i64, i64> &m, i64 branches = 0) const {
    if (word) {
      m[branches]++;
    }
    if (branches == 0 || word || children_count() > 1) {
      branches++;
    }
    for (const unique_ptr<Trie> &child : children) {
      if (child) {
        child->branch_count(m, branches);
      }
    }
  }
};
