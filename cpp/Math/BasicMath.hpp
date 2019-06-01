#include "../template.hpp"

lint gcd(lint a, lint b) { return b != 0 ? gcd(b, a % b) : a; }
lint lcm(lint a, lint b) { return a / gcd(a, b) * b; }

bool isPrime(int n) {
	if (n < 2) return 0;
	for (int i = 2; i * i <= n; ++i) if (n % i == 0) return 0;
	return 1;
}

lint extgcd(lint a, lint b, lint &x, lint &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	lint d = extgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

lint invmod(lint a, lint MOD) {
    lint x, y;
    extgcd(a, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}

lint powmod(lint x, lint k, lint MOD) {
	lint ret = 1;	
	while (k > 0) {
		if (k & 1) modMul(ret, x, MOD);
		modMul(x, x, MOD);
		k >>= 1;
	}
	return ret;
}
