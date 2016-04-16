#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

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