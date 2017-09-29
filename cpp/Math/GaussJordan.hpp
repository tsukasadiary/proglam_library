#include "MatrixOperation.hpp"

Vec< double > gaussJordan(const Matrix< double >& A, const Vec< double >& b) {
	int n = A.size();
	Matrix< double > B(n, Vec< double >(n + 1));
	
	for_(i,0,n) for_(j,0,n) B[i][j] = A[i][j];
	
	for_(i,0,n) B[i][n] = b[i];
	
	for_(i,0,n) {
		int piv = i;
		for_(j,i,n) if (fabs(B[j][i]) > fabs(B[piv][i])) piv = j;
		swap(B[i], B[piv]);
		
		if (fabs(B[i][i]) < EPS) return Vec< double >();
		
		for_(j,i+1,n+1) B[i][j] /= B[i][i];
		
		for_(j,0,n) {
			if (i != j) {
				for_(k,i+1,n+1) B[j][k] -= B[j][i] * B[i][k];
			}
		}
	}
	
	Vec< double > res(n);
	for_(i,0,n) res[i] = B[i][n];
	return res;
}
