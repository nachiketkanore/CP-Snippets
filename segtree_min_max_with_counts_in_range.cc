
const int N = 1e5 + 5, inf = 1e18;

int a[N];

class node {
public:
	int mn, mx;
	int cnt_mn, cnt_mx;

	node() { mn = inf, mx = -inf, cnt_mx = cnt_mn = 0; }
	node(int mn_, int mx_) { mn = mn_, mx = mx_, cnt_mx = cnt_mn = 1; }
	
};
class segTree {
public:
	
	node merge(node& one, node& two) {
		node ret;
		ret.mx = max(one.mx, two.mx);
		ret.mn = min(one.mn, two.mn);
		if (one.mx > two.mx) ret.cnt_mx = one.cnt_mx;
		else if (two.mx > one.mx) ret.cnt_mx = two.cnt_mx;
		else ret.cnt_mx = one.cnt_mx + two.cnt_mx;

		if (one.mn < two.mn) ret.cnt_mn = one.cnt_mn;
		else if (two.mn < one.mn) ret.cnt_mn = two.cnt_mn;
		else ret.cnt_mn = one.cnt_mn + two.cnt_mn;
		
		return ret;
	}
	vector<node> t;

	void build(int u, int tl, int tr) {
		if (tl == tr) {
			t[u] = node(a[tl], a[tr]);
			return;
		}
		int mid = (tl+tr)/2;
		build(2*u, tl, mid);
		build(2*u+1, mid+1, tr);
		t[u] = merge(t[2*u], t[2*u+1]);
	}

	node get(int u, int tl, int tr, int ql, int qr) {
		if (tl > tr || ql > qr) return node();
		if (tl == ql && tr == qr) return t[u];
		int mid = (tl+tr)/2;
		node left = get(2*u, tl, mid, ql, min(qr, mid));
		node right = get(2*u+1, mid+1, tr, max(mid+1, ql), qr);
		return merge(left, right);
	}

	void init(int n) {
		t.clear();
		t = vector<node> ((n<<2)+2);
		build(1,1,n);
	}
} tree;
