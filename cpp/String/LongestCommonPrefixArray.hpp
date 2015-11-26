#include "SaffixArray.hpp"

class LongestCommonPrefixArray {
private:
	Vec< int > rank;
	
public:
	LongestCommonPrefixArray() {}
	
	Vec< int > construct(const SaffixArray& sa) {
		int n = sa.length();
		const string& text = sa.getText();
		
		rank.assign(n + 1, 0);
		for_(i,0,n+1) rank[sa.getSA(i)] = i;
		
		Vec< int > lcp(n, 0);
		int h = 0;
		
		for_(i,0,n) {
			int j = sa.getSA(rank[i] - 1);
			if (h > 0) --h;
			for (; i + h < n && j + h < n && text[i + h] == text[j + h]; ++h);
			lcp[rank[i] - 1] = h;
		}
		
		return lcp;
	}
};
