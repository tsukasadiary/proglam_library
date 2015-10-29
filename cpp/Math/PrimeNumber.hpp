#include "BasicMath.hpp"

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