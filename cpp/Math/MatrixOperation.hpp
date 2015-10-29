#include "BasicMath.hpp"

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