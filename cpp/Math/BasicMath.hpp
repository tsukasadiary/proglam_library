#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.h"
#endif

#ifndef BASIC_MATH_HPP
#define BASIC_MATH_HPP

lint fact(lint x) {
	if (x <= 1) return 1;
	return x * fact(x - 1);
}

lint combination(lint n, lint m) {
	lint res = 1;
	if (2 * m > n) m = n - m;
	for_(i,0,m) res = res * (n - i) / (i + 1);
	return res;
}

template< typename T >
T POW(T x, T k) {
	T res = 1;
	
	while (k > 0) {
		if (k & 1) res *= x;
		x *= x;
		k >>= 1;
	}
	
	return res;
}

lint gcd(lint a, lint b) {
	return b != 0 ? gcd(b, a % b) : a;
}

lint lcm(lint a, lint b) {
	return a / gcd(a, b) * b;
}

bool isPrime(int n) {
	if (n < 2) return 0;
	for (int i = 2; i * i <= n; ++i) if (n % i == 0) return 0;
	return 1;
}

template< typename T >
T extgcd(T a, T b, T& x, T& y) {
	T g = 1; x = 1; y = 0;
	if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
	return g;
}

template< typename T >
T invMod(T a, T mod) {
	T x, y;
	if (extgcd(a, mod, x, y) == -1) return (x + mod) % mod;
	return 0;
}

#endif // BASIC_MATH_HPP
