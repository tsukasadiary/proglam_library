#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// KMP
class KMP {
private:
	vector<int> fail;
	
public:
	KMP() {}
	
	int match(string _t, string _p) {
		int _n = size_of(_t), _m = size_of(_p);
		
		fail.assign(_m + 1, 0);
		int j = fail[0] = -1;
		
		for_(i,1,_m + 1) {
			while (j >= 0 && _p[j] != _p[i - 1]) j = fail[j];
			fail[i] = ++j;
		}
		
		int count = 0;
		for (int i = 0, k = 0; i < _n; ++i) {
			while (k >= 0 && _p[k] != _t[i]) k = fail[k];
			if (++k >= _m) {
				++count;
				k = fail[k];
			}
		}
		
		return count;
	}	
};