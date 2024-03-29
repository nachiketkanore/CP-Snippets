
// can be used for Range min/max/gcd range query in O(1)
class sparseTable {
public:
  int RMQ[20][N];
  int floorlog[N];

  void precompute(int n) {
    for (int i = 0; (1 << i) < N; i++) {
      for (int j = (1 << i); j < N && j < (1 << (i + 1)); j++)
        floorlog[j] = i;
    }

    for (int i = n; i >= 1; i--) {
      RMQ[0][i] = arr[i];            // leaf value
      int mxj = floorlog[n - i + 1]; // 2^j <= n-i+1
      int pw = 1;
      for (int j = 1; j <= mxj; j++) {
        RMQ[j][i] = gcd(RMQ[j - 1][i], RMQ[j - 1][i + pw]); // operation
        pw <<= 1;
      }
    }
  }

  int query(int L, int R) {
    int k = floorlog[R - L + 1];                     // 2^k <= R-L+1
    return gcd(RMQ[k][L], RMQ[k][R - (1 << k) + 1]); // operation
  }
} T;
