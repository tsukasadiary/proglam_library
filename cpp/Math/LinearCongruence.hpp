#include "BasicMath.hpp"

pii linearCongruence(const Vec< int >& A, const Vec< int >& B, const Vec< int >& M) {
	int x = 0, m = 1, n = size_of(A);
	
	for_(i,0,n) {
		int a = A[i] * m, b = B[i] - A[i] * x, d = gcd(M[i], a);
		if (b % d != 0) return pii(0, -1);
		int t = b / d * invMod(a / d, M[i] / d) % (M[i] / d);
		x = x + m * t;
		m *= M[i] / d;
	}
	
	return pii(x % m, m);
}
