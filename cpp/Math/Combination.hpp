#include "../template.hpp"

class Combination {
private:
	const int MAX_NUM;
	vector< lint > fact, inv;
	const lint MOD;
	
	lint powMod(lint x, lint k) {
		lint res = 1;
		while (k) {
			if (k&1) modMul(res, x, MOD);
			modMul(x, x, MOD);
			k >>= 1;
		}
		return res;
	}
	
	void pre() {
		fact[0] = fact[1] = 1;
		for_(i,2,MAX_NUM) fact[i] = (fact[i-1] * i) % MOD;
		for_(i,0,MAX_NUM) inv[i] = powMod(fact[i], MOD-2);
	}
	
public:
	Combination(int __MAX_NUM, lint __MOD)
	: MAX_NUM(__MAX_NUM), fact(__MAX_NUM, 0), inv(__MAX_NUM, 0), MOD(__MOD) { pre(); }
	
	lint calc(int n, int k) {
		if (n < k) return 0;
		lint res = fact[n];
		modMul(res, inv[n-k], MOD);
		modMul(res, inv[k], MOD);
		return res;
	}
};
