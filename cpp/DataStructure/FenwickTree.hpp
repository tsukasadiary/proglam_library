#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

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