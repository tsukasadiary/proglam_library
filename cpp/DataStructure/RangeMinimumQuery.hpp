#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

template< typename T >
class RangeMinimumQuery {
private:
	int N;
	Vec< T > rmq;
	
public:
	RangeMinimumQuery() {}
	RangeMinimumQuery(Vec< T >& ary) { build(ary); }
	
	void build(Vec< T >& ary) {
		N = size_of(ary);
		
		int logN = 1;
		for (int k = 1; k < N; k *= 2) ++logN;
		
		int *r = new int[N * logN];
		int *b = r; copy(ary.begin(), ary.begin() + N, b);
		
		for (int k = 1; k < N; k *= 2) {
			copy(b, b + N, b + N); b += N;
			for_(i,0,N-k) b[i] = min(b[i], b[i + k]);
		}
		
		rmq.assign(N * logN, 0);
		int len = N * logN;
		for_(i,0,len) rmq[i] = r[i];
		
		delete [] r;
	}
	
	T query(int l, int r) {//[l,r]
		int z = r - l, k = 0, e = 1, s;
		s = ( (z & 0xffff0000) != 0 ) << 4; z >>= s; e <<= s; k |= s;
		s = ( (z & 0x0000ff00) != 0 ) << 3; z >>= s; e <<= s; k |= s;
		s = ( (z & 0x000000f0) != 0 ) << 2; z >>= s; e <<= s; k |= s;
		s = ( (z & 0x0000000c) != 0 ) << 1; z >>= s; e <<= s; k |= s;
		s = ( (z & 0x00000002) != 0 ) << 0; z >>= s; e <<= s; k |= s;
		return min( rmq[l + N * k], rmq[r + N * k - e + 1] );
	}
};