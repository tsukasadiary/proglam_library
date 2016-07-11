#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

// Segment Tree
template< typename DATA, class CALC, DATA FAIL >
class SegmentTree {
private:
	int size__;
	Vec< DATA > data;
	
	inline int left_t(int k) { return (k << 1) + 1; }
	inline int right_t(int k) { return (k << 1) + 2; }
	inline int center(int l, int r) { return (l + r) >> 1; }
	
	DATA calc(DATA d1, DATA d2) { return CALC().calc(d1, d2); }
	
	DATA query(int a, int b, int k, int l, int r) {
		if (r <= a || b <= l) return FAIL;
		if (a <= l && r <= b) return data[k];
		return calc(query(a, b, left_t(k), l, center(l, r)),
					query(a, b, right_t(k), center(l, r), r));
	}
	
public:
	SegmentTree(int n, DATA ini) {
		for (size__ = 1; size__ < n; size__ <<= 1);
		data.assign(2 * size__ - 1, ini);
	}
	
	void update(int k, DATA a) {
		k += size__ - 1;
		data[k] = a;
		
		while (k > 0) {
			k = (k - 1) >> 1;
			data[k] = calc(data[left_t(k)], data[right_t(k)]);
		}
	}
	
	DATA query(int a, int b) { return query(a, b, 0, 0, size__); }
	
	int size() { return size__; }
};

template< typename T >
class MaxCalc {
public:
	inline T calc(T d1, T d2) { return max(d1, d2); }
};

template< typename T >
class MinCalc {
public:
	inline T calc(T d1, T d2) { return min(d1, d2); }
};