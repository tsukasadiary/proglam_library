#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

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