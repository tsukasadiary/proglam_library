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
