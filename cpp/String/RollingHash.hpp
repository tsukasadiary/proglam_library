#ifndef ROLLING_HASH_HPP
#define ROLLING_HASH_HPP

#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.h"
#endif

typedef unsigned long long ull;
const ull BASE = 1e9 + 7;

class RollingHash {
private:	
	int N;
	const string& text;
	vector< ull > mul;
	vector< ull > hash;
	
	void makeHash() {
		for_(i,1,N+1) {
			mul[i] = mul[i - 1] * BASE;
			hash[i] = hash[i - 1] * BASE + text[i - 1];
		}
	}
	
public:
	RollingHash(string& _text_)
	: N(_text_.size()), text(_text_), mul(N + 1, 1), hash(N + 1, 0) {
		makeHash();
	}
	
	ull getHash(int l, int r) {
		return hash[r] - hash[l - 1] * mul[r - l + 1];
	}
};

#endif // ROLLING_HASH_HPP