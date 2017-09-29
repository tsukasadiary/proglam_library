#include "PrimeNumber.hpp"
#include "GaussJordan.hpp"
#include "EulerPhi.hpp"
#include "FFT.hpp"
#include "LinearCongruence.hpp"

int main() {
	PrimeNumber pn(100);
	int n = pn.getNum();
	for_(i,0,n) cout << pn.get(i) << endl;
}
