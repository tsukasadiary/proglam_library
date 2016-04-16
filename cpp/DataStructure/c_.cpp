// tsukasa_diary's programing contest code template
#include <bits/stdc++.h>
using namespace std;
#define TSUKASA_DIARY_S_TEMPLATE
// define
#define for_(i,a,b) for(int i=(a);i<(b);++i)
#define for_rev(i,a,b) for(int i=(a);i>=(b);--i)
#define allof(a) (a).begin(),(a).end()
#define minit(a,b) memset(a,b,sizeof(a))
#define size_of(a) int((a).size())
#define cauto const auto
// typedef
typedef long long lint;
typedef double Double;
typedef pair< int, int > pii;
template< typename T > using Vec = vector< T >;
template< typename T > using Matrix = Vec< Vec< T > >;
template< typename T > using USet = unordered_set< T >;
template< typename T, class C > using MyUSet = unordered_set< T, C >;
template< typename T, typename F > using UMap = unordered_map< T, F >;
template< typename T, typename F, class C > using MyUMap = unordered_map< T, F, C >;
// hash
class PiiHash { public: size_t operator () (const pii& p) const { return (p.first << 16) | p.second; } };
// popcount
inline int POPCNT(int x) { return __builtin_popcount(x); }
inline int POPCNT(lint x) { return __builtin_popcount(x); }
// inf
const int iINF = 1L << 30;
const lint lINF = 1LL << 60;
// eps
const Double EPS = 1e-9;
const Double PI = acos(-1);
// inrange
template< typename T >
inline bool in_range(T v, T mi, T mx) { return mi <= v && v < mx; }
template< typename T >
inline bool in_range(T x, T y, T W, T H) { return in_range(x,0,W) && in_range(y,0,H); }
// neighbor clockwise
const int DX[4] = {0,1,0,-1}, DY[4] = {-1,0,1,0};
const int DX_[8] = {0,1,1,1,0,-1,-1,-1}, DY_[8] = {-1,-1,0,1,1,1,0,-1};
// variable update
template< typename T > inline void modAdd(T& a, T b, T mod) { a = (a + b) % mod; }
template< typename T > inline void minUpdate(T& a, T b) { a = min(a, b); }
template< typename T > inline void maxUpdate(T& a, T b) { a = max(a, b); }
// converter
template< typename F, typename T >
inline void convert(F& from, T& to) {
	stringstream ss;
	ss << from; ss >> to;
}

template< typename T >
class Treap {
private: // parts
	unsigned int rnd() {
		static unsigned int x = 123456789, y = 362436069, z = 521288629, w = 88675123;
		unsigned int t = (x ^ (x << 11));
		x = y; y = z; z = w;
		return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
	}
	
	struct Node {
		T val, data, add;
		Node *lch, *rch;
		int pri, cnt;
		bool rev;
		
		Node(T v, int p) : val(v), data(v), add(T(0)), pri(p), cnt(1), rev(false) { lch = rch = nullptr; }
	};
	
	Node *root;
	
private: // main function
	int count(Node* t) { return t ? t->cnt : 0; }
	T data(Node* t) { return t ? t->data : T(iINF); }	
	T calc(T val1, T val2) { return min(val1, val2); }
	
	void push(Node* t) {
		if (t && t->rev) {
			swap(t->lch, t->rch);
			if (t->lch) t->lch->rev ^= true;
			if (t->rch) t->rch->rev ^= true;
			t->rev = false;
		}
		
		if (t && t->add != 0) {
			t->val += t->add;
			if (t->lch) t->lch->add += t->add;
			if (t->rch) t->rch->add += t->add;
			t->add = 0;
		}
	}
	
	Node* update(Node *t) {
		if (!t) return t;
		t->cnt = count(t->lch) + count(t->rch) + 1;
		t->data = calc(calc(data(t->lch), data(t->rch)), t->val);
		return t;
	}
	
	Node* merge(Node* l, Node* r) {
		push(l); push(r);
		
		if (!l || !r) return l ? l : r;
	
		if (l->pri > r->pri) {
			l->rch = merge(l->rch, r);
			return update(l);
		} else {
			r->lch = merge(l, r->lch);
			return update(r);
		}
	}
	
	typedef pair< Node*, Node* > pnn;
	
	pnn split(Node* t, int k) {
		if (!t) return pnn(nullptr, nullptr);
		
		push(t);
		
		if (k <= count(t->lch)) {
			pnn s = split(t->lch, k);
			t->lch = s.second;
			return pnn(s.first, update(t));
		} else {
			pnn s = split(t->rch, k - count(t->lch) - 1);
			t->rch = s.first;
			return pnn(update(t), s.second);
		}
	}
	
	Node* insert(Node* t, int k, T val, int pri) {
		pnn s = split(t, k);
		t = merge(s.first, new Node(val, pri));
		t = merge(t, s.second);
		return update(t);
	}
	
	Node* erase(Node* t, int k) {
		pnn s1 = split(t, k + 1);
		pnn s2 = split(s1.first, k);
		t = merge(s2.first, s1.second);
		delete s2.second;
		return update(t);
	}
	
	Node* find(Node* t, int k) {
		push(t);
		int c = count(t->lch);
		if (k < c) return find(t->lch, k);
		if (k > c) return find(t->rch, k - c - 1);
		return t;
	}
	
	void dump(Node* t, ostream& os) {
		if (!t) return;
		os << "(";
		dump(t->lch, os);
		os << t->val;
		dump(t->rch, os);
		os << ")";
	}
	
public: // public function
	Treap() : root(nullptr) {}
	
	void insert(int k, T val) { root = insert(root, k, val, rnd()); }
	void erase(int k) { root = erase(root, k); }
	Node* find(int k) { return find(root, k); }
	int size() { return count(root); }
	
	void dump(ostream& os) {
		dump(root, os);
		os << endl;
	}
	
	~Treap() { while (root) erase(0); }
	
public: // query implement
	void shift(int l, int r) {// AOJ1508-RMQ- : [l,r) right-shift
		pnn a, b, c;
		a = split(root, r);
		b = split(a.first, r - 1);
		c = split(b.first, l);
		root = merge(c.first, b.second);
		root = merge(root, c.second);
		root = merge(root, a.second);
	}
	
	void reverse(int l, int r) {
		pnn a, b;
		a = split(root, r);
		b = split(a.first, l);
		b.second->rev ^= true;
		root = merge(b.first, b.second);
		root = merge(root, a.second);
	}
	
	void rangeAdd(int l, int r, int v) {
		pnn a, b;
		a = split(root, r);
		b = split(a.first, l);
		b.second->add += v;
		root = merge(b.first, b.second);
		root = merge(root, a.second);
	}
	
	T query(int l, int r, Node* t) {
		int c = count(t);
		
		if (l >= c || r <= 0) return T(iINF);
		if (l <= 0 && r >= c) return data(t);
		
		c = count(t->lch);
		int res = calc(query(l, r, t->lch), query(l - c - 1, r - c - 1, t->rch));
		if (l <= c && c < r) res = calc(res, t->val);
		return res;
	}
	
	T query(int l, int r) { return query(l, r, root); }
};

int main() {
	int n, m;
	cin >> n >> m;
	
	Vec< int > a(n);
	for_(i,0,n) cin >> a[i];
	
	Vec< int > t(m), r(m);
	for_(i,0,m) cin >> t[i] >> r[i];
	
	Vec< int > order(m);
	for_(i,0,m) order[i] = i;
	
	sort(allof(order), [&](int a, int b) {
		return (r[a] == r[b]) ? a > b : r[a] > r[b];
	});
	
	int fo = order[0];
	if (t[fo] == 1) sort(a.begin(), a.begin() + r[fo]);
	else sort(a.begin(), a.begin() + r[fo], greater< int >());
	
	Treap< int > treap;
	for_(i,0,n) treap.insert(i, a[i]);
	
	int T = t[fo];
	
	for_(i,1,m) {
		if (fo > order[i]) continue;
		
		fo = order[i];
		
		if (T != t[fo]) {
			treap.reverse(0, r[fo]);
			T = t[fo];
		}
	}
	
	for_(i,0,n) cout << treap.query(i, i+1) << (i < n - 1 ? " " : "\n");
}