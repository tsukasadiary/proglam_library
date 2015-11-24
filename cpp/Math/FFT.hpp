#include "BasicMath.hpp"

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
Vec< T > convolution(Vec< T >& a, Vec< T >& b) {
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
