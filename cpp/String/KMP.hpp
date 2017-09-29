#include "../template.hpp"

class KMP {
private:
	Vec<int> fail;
	
public:
	KMP() {}
	
	int match(string t, string p) {
		int n = t.size(), m = p.size();
		
		fail.assign(m + 1, 0);
		int j = fail[0] = -1;
		
		for_(i,1,m + 1) {
			while (j >= 0 && p[j] != p[i - 1]) j = fail[j];
			fail[i] = ++j;
		}
		
		int count = 0;
		for (int i = 0, k = 0; i < n; ++i) {
			while (k >= 0 && p[k] != t[i]) k = fail[k];
			if (++k >= m) {
				++count;
				k = fail[k];
			}
		}
		
		return count;
	}	
};
