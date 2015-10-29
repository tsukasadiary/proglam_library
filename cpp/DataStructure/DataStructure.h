#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// Coordinate Compression
template< typename DATA >
class CoordinateCompression {
public:	
	struct Result {
		int H, W;
		Vec< int > X1, Y1, X2, Y2;
	};
	
	int N;
	Result res;	
	
	int compress(Vec< int >& x1, Vec< int >& x2, int W) {
		Vec< int > xs;
		
		for_(i,0,N) for_(j,-1,2) {
			int nx1 = x1[i] + j, nx2 = x2[i] + j;
			if (0 <= nx1 && nx1 < W) xs.push_back(nx1);
			if (0 <= nx2 && nx2 < W) xs.push_back(nx2);
		}
		
		sort(allof(xs));
		xs.erase(unique(allof(xs)), xs.end());
		
		for_(i,0,N) {
			x1[i] = find(allof(xs), x1[i]) - xs.begin();
			x2[i] = find(allof(xs), x2[i]) - xs.begin();
		}
		
		return xs.size();
	}
	
public:
	CoordinateCompression(int _H_, int _W_, 
						  Vec< int >& _X1_, Vec< int >& _Y1_, Vec< int >& _X2_, Vec< int >& _Y2_)
	: N(_X1_.size()), res(Result{_H_, _W_, _X1_, _Y1_, _X2_, _Y2_}) {}
	
	Result compression() {
		res.W = compress(res.X1, res.X2, res.W);
		res.H = compress(res.Y1, res.Y2, res.H);
		return res;
	}
};

// union-find
class UnionFind {
private:
	Vec< int > data;
	int num_of_g;
	
public:
	UnionFind(int n) : data(n, -1), num_of_g(n) {}
	
	bool unionSet(int x, int y) {
		x = root(x); y = root(y);
		
		if (x == y) return 0;
		
		if (data[y] < data[x]) swap(x, y);
		data[x] += data[y]; data[y] = x;
		--num_of_g;
		
		return 1;
	}
	
	bool sameSet(int x, int y) { return root(x) == root(y); }
	int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
	int size(int x) { return -data[root(x)]; }
	int getNumOfG() { return num_of_g; }
};

// Segment Tree
template< typename DATA >
class SegmentTree {
private:
	int size__;
	Vec< DATA > data;
	
	inline int left_t(int k) { return (k << 1) + 1; }
	inline int right_t(int k) { return (k << 1) + 2; }
	inline int center(int l, int r) { return (l + r) >> 1; }
	
	void update(int k, DATA a) {
		k += size__ - 1;
		data[k] = a;
		
		while (k > 0) {
			k = (k - 1) >> 1;
			data[k] = calc(data[left_t(k)], data[right_t(k)]);
		}
	}
	
	DATA query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) return (DATA)iINF;
		if (a <= l && r <= b) return data[k];
		return calc(query(a, b, left_t(k), l, center(l, r)),
					query(a, b, right_t(k), center(l, r), r));
	}
	
public:
	SegmentTree(int n, DATA ini) {
		for (size__ = 1; size__ < n; size__ <<= 1);
		data.assign(2 * size__ - 1, ini);
	}
	
	DATA calc(DATA d1, DATA d2) { return min(d1, d2); }
	
	DATA query(int a, int b) { return query(a, b, 0, 0, size__); }
	
	int size() { return size__; }
};

// Segment Tree with Lazy Evaluate
template< typename DATA >
class SegmentTreeLazy {
private:
	int size__;
	Vec< DATA > data, lazy;
	
	inline int left_t(int k) { return (k << 1) + 1; }
	inline int right_t(int k) { return (k << 1) + 2; }
	inline int center(int l, int r) { return (l + r) >> 1; }
	
private:
	DATA calc(DATA d1, DATA d2) { return d1 + d2; }
	
	void lazyCalc(int k, DATA val) { lazy[k] += val; }
	
	inline void lazyEval(int l, int r, int k) {
		data[k] += lazy[k] * (r - l);
		
		if (k < size__ - 1) {
			lazyCalc(left_t(k), lazy[k]);
			lazyCalc(right_t(k), lazy[k]);
		}
		
		lazy[k] = DATA(0);
	}
	
	inline void updateAt(int k) { data[k] = calc(data[left_t(k)], data[right_t(k)]); }
	
	void update(int a, int b, DATA x, int k, int l, int r) {
		lazyEval(l, r, k);
		
		if (r <= a || b <= l) return;
		if (a <= l && r <= b) {
			lazyCalc(k, x);
			lazyEval(l, r, k);
			return;
		}
		
		update(a, b, x, left_t(k), l, center(l, r));
		update(a, b, x, right_t(k), center(l, r), r);
		updateAt(k);
	}
	
	DATA query(int a, int b, int k, int l, int r) {
		lazyEval(l, r, k);
		
		if (r <= a || b <= l) return 0;
		if (a <= l && r <= b) return data[k];
		DATA res =  calc(query(a, b, left_t(k), l, center(l, r)),
						 query(a, b, right_t(k), center(l, r), r));
		
		updateAt(k);
		return res;
	}
	
public:
	SegmentTreeLazy() {}
	
	SegmentTreeLazy(int n, DATA ini, DATA lini) {
		for (size__ = 1; size__ < n; size__ <<= 1);
		data.assign(2 * size__ - 1, ini);
		lazy.assign(2 * size__ - 1, lini);
	}
	
	void update(int a, int b, DATA x) { update(a, b, x, 0, 0, size__); }
	
	DATA query(int a, int b) { return query(a, b, 0, 0, size__); }
	
	int size() { return size__; }
};

// Range Add Segment Tree
template< typename DATA >
class SegmentTreeR {
private:
	int size__;
	Vec< DATA > data, adds;
	
	inline int left_t(int k) { return (k << 1) + 1; }
	inline int right_t(int k) { return (k << 1) + 2; }
	inline int center(int l, int r) { return (l + r) >> 1; }
	
private:
	void rangeAdd(int a, int b, DATA x, int k, int l, int r) {
		if (r <= a || b <= l) return;
		
		if (a <= l && r <= b) {
			adds[k] += x;
			return;
		}
		
		data[k] += x * (min(r, b) - max(l, a));
		rangeAdd(a, b, x, left_t(k), l, center(l, r));
		rangeAdd(a, b, x, right_t(k), center(l, r), r);
	}
	
	DATA query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) return 0;
		if (a <= l && r <= b) return data[k] + adds[k] * (r - l);
		return query(a, b, left_t(k), l, center(l, r))
				+ query(a, b, right_t(k), center(l, r), r)
				+ adds[k] * (min(r, b) - max(l, a));
	}
	
public:
	SegmentTreeR() {}
	
	SegmentTreeR(int n, DATA ini, DATA aini) {
		for (size__ = 1; size__ < n; size__ <<= 1);
		data.assign((size__ << 1) - 1, ini);
		adds.assign((size__ << 1) - 1, aini);
	}
	
	void rangeAdd(int a, int b, DATA x) { rangeAdd(a, b, x, 0, 0, size__); }
	
	DATA query(int a, int b) { return query(a, b, 0, 0, size__); }
	
	int size() { return size__; }
};

// BIT (fenwick tree)
template< typename DATA >
class FenwickTree {
private:
	int size__;
	Vec< DATA > data;
	
public:
	FenwickTree(int n) : size__(n), data(n + 1, DATA()) {}
	
	DATA sum(int i) {
		DATA res = DATA();
		
		while (i > 0) {
			res += data[i];
			i -= i & -i;
		}
		
		return res;
	}
	
	void add(int i, DATA x) {
		while (i <= size__) {
			data[i] += x;
			i += i & -i;
		}
	}
};

// Dancing Links
template< typename DATA >
class DancingLinks {
private:
	struct Node {
		int r, c;
		DATA data;
		Node *lft, *rgt, *up, *dwn;
		Node() : r(-1), c(-1) {}
		Node(int _r_, int _c_, DATA _d_) : r(_r_), c(_c_), data(_d_) {}
	};
	
	int N, M;
	const Vec< Vec< DATA > >& mat;
	DATA zero;
	
	Node head;
	Vec< Node > row;
	Vec< Node > col;
	Vec< Node > cell;
	
private:
	void makeLinks() {
		row = Vec< Node >(N);		
		col = Vec< Node >(M);
		
		head.up = &row[N - 1]; row[N - 1].dwn = &head;
		head.dwn = &row[0]; row[0].up = &head;
		
		for_(r,0,N) row[r].lft = row[r].rgt = &row[r];
		
		for_(r,1,N) {
			row[r - 1].dwn = &row[r];
			row[r].up = &row[r - 1];
		}
		
		head.lft = &col[M - 1]; col[M - 1].rgt = &head;
		head.rgt = &col[0]; col[0].lft = &head;
		
		for_(c,0,M) col[c].up = col[c].dwn = &col[c];
		
		for_(c,1,M) {
			col[c - 1].rgt = &col[c];
			col[c].lft = &col[c - 1];
		}
		
		cell.clear();
		
		Vec< Node* > cur(M);
		for_(c,0,M) cur[c] = &col[c];
		
		int non_zero_cnt = 0;
		for_(r,0,N) for_(c,0,M) if (mat[r][c] != zero) ++non_zero_cnt;
		
		cell.assign(non_zero_cnt, Node());
		
		for_(r,0,N) {
			Node* p = &row[r];
			
			for_(c,0,M) {
				if (mat[r][c] != zero) {
					int i = --non_zero_cnt;
					cell[i] = Node(r, c, mat[r][c]);
					
					p->rgt = &cell[i];
					cell[i].lft = p;
					
					cell[i].rgt = &row[r];
					row[r].lft = &cell[i];
					
					cell[i].up = cur[c];
					cur[c]->dwn = &cell[i];
					
					col[c].up = &cell[i];
					cell[i].dwn = &col[c];
							
					p = cur[c] = &cell[i];
				}
			}
		}
	}
	
public:
	DancingLinks(const Vec< Vec< DATA > >& _mat_, DATA _zero_)
	: N(_mat_.size()), M(_mat_[0].size()), mat(_mat_), zero(_zero_) {
		makeLinks();
	}
	
	void deleteRow(int r) {
		Node* p = &row[r];
		
		do {
			(p->up)->dwn = p->dwn;
			(p->dwn)->up = p->up;
			p = p->rgt;
		} while (p != &row[r]);
	}
	
	void restoreRow(int r) {
		Node* p = &row[r];
		
		do {
			(p->up)->dwn = p;
			(p->dwn)->up = p;
			p = p->rgt;
		} while (p != &row[r]);
	}
	
	void deleteCol(int c) {
		Node* p = &col[c];
		
		do {
			(p->lft)->rgt = p->rgt;
			(p->rgt)->lft = p->lft;
			p = p->dwn;
		} while (p != &col[c]);
	}
	
	void restoreCol(int c) {
		Node* p = &col[c];
		
		do {
			(p->lft)->rgt = p;
			(p->rgt)->lft = p;
			p = p->dwn;
		} while (p != &col[c]);
	}
	
	Vec< Vec< DATA > > current() {
		Vec< Vec< DATA > > res(N, Vec< DATA >(M, zero));
		
		Node* p = &head;
		
		while (p->dwn != &head) {
			p = p->dwn;
			Node* q = p;
			
			while (q->rgt != p) {
				q = q->rgt;
				res[q->r][q->c] = q->data;
			}			
		}
		
		return res;
	}
};

#endif