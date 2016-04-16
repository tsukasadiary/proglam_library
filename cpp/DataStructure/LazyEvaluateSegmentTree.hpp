#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

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