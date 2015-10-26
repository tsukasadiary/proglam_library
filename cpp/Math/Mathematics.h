#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

/*** Mathematics ***/
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

lint POW(lint x, lint k) {
	lint res = 1;
	
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

lint extgcd(lint a, lint b, lint& x, lint& y) {
	lint g = 1; x = 1; y = 0;
	if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
	return g;
}

lint invMod(lint a, lint mod) {
	lint x, y;
	if (extgcd(a, mod, x, y) == -1) return (x + mod) % mod;
	return 0;
}

bool isGaussianPrime(int a, int b) {
	if (a < 0) a = -a;
	if (b < 0) b = -b;
	if (a == 0) return b % 4 == 3 && isPrime(b);
	if (b == 0) return a % 4 == 3 && isPrime(a);
	return isPrime(a * a + b * b);
}

class PrimeNumber {
private:
	int upper;
	Vec< int > primes;
	Vec< int > prime_nums;
	
public:
	PrimeNumber(int n) : upper(n) {
		enum_primes();
	}
	
	void enum_primes() {
		primes.clear();
		prime_nums.assign(upper + 1, 0);
		Vec< bool > isprime(upper + 1, 1);
		
		for_(i,2,upper+1) {
			if (isprime[i]) {
				++prime_nums[i];
				primes.push_back(i);
				for (int j = 2 * i; j <= upper; j += i) isprime[j] = 0;
			}
			
			prime_nums[i] += prime_nums[i - 1];
		}
	}
	
	int prime_count(int upper_num) {
		return prime_nums[upper_num];
	}
	
	int prime_count(int mi, int mx) {
		return prime_nums[mx] - prime_nums[mi - 1];
	}
	
	int at(int i) {
		return primes[i];
	}
};

// matrix operation
template< typename T >
Matrix< T > operator + (const Matrix< T >& a, const Matrix< T >& b) {
	int n = size_of(a), m = size_of(a[0]);
	Matrix< T > res(n, Vec< T >(m, T()));
	for_(i,0,n) for_(j,0,m) res[i][j] = a[i][j] + b[i][j];
	return res;
}

template< typename T >
Matrix< T > operator - (const Matrix< T >& a, const Matrix< T >& b) {
	int n = size_of(a), m = size_of(a[0]);
	Matrix< T > res(n, Vec< T >(m, T()));
	for_(i,0,n) for_(j,0,m) res[i][j] = a[i][j] - b[i][j];
	return res;
}

template< typename T >
Matrix< T > operator * (const Matrix< T >& a, const Matrix< T >& b) {
	int n = size_of(a), m = size_of(b), l = size_of(b[0]);
	Matrix< T > res(n, Vec< T >(m, T()));
	for_(i,0,n) for_(k,0,l) for_(j,0,m) res[i][j] = a[i][k] * b[k][j];
	return res;
}

template< typename T >
Matrix< T > MatrixI(int n) {
	Matrix< T > res(n, Vec< T >(n, T()));
	for_(i,0,n) res[i][i] = T(1);
	return res;
}

template< typename T >
Matrix< T > POW(Matrix< T >& a, lint k) {
	int n = size_of(a);
	Matrix< T > res = MatrixI< T >(n);
	
	while (k > 0) {
		if (k & 1) res = res * a;
		a = a * a;
		k >>= 1;
	}
	
	return res;
}

// FFT
typedef complex< double > Complex;

void FFT(Vec< Complex >& f, int n, bool inverse) {
	if (n == 1) return;
	
	Vec< Complex > f0, f1;
	for_(i,0,n/2) {
		f0.push_back(f[2*i]);
		f1.push_back(f[2*i+1]);
	}
	
	FFT(f0, n/2, inverse);
	FFT(f1, n/2, inverse);
	
	double eps = (inverse ? -2.0 : 2.0) * PI / (double)n;
	Complex zeta(cos(eps), sin(eps)), pow_zeta(1, 0);
	
	for_(i,0,n) {
		f[i] = f0[i % (n/2)] + pow_zeta * f1[i % (n/2)];
		pow_zeta *= zeta;
	}
}

template< typename T >
Vec< T > comvolution(Vec< T >& a, Vec< T >& b) {
	int n = 1;
	while (n <= size_of(a) + size_of(b)) n <<= 1;
	
	Vec< Complex > ca, cb;
	for_(i,0,n) {
		if (i < size_of(a)) ca.push_back(Complex(a[i], 0));
		else ca.push_back(Complex(0, 0));
		if (i < size_of(b)) cb.push_back(Complex(b[i], 0));
		else cb.push_back(Complex(0, 0));
	}
	
	FFT(ca, n, false);
	FFT(cb, n, false);
	
	Vec< Complex > ab(n);
	for_(i,0,n) ab[i] = ca[i] * cb[i];
	
	FFT(ab, n, true);
	for_(i,0,n) ab[i] /= Complex((double)n, 0);
	
	Vec< T > res;
	for_(i,0,n) res.push_back(T(ab[i].real() + 0.5));
	
	return res;
}

#endif // MATHEMATICS_H