#include "../template.hpp"

class PrimeNumber {
private:
	int MAX_NUM;
	Vec< int > primes, prime_nums;
	
public:
	PrimeNumber(int n) : MAX_NUM(n), prime_nums(MAX_NUM+1) { enum_primes(); }
	
	void enum_primes() {
		Vec< bool > isprime(MAX_NUM + 1, true);
		for_(i,2,MAX_NUM+1) {
			if (isprime[i]) {
				++prime_nums[i];
				primes.push_back(i);
				for (int j = 2 * i; j <= MAX_NUM; j += i) isprime[j] = 0;
			}
			prime_nums[i] += prime_nums[i - 1];
		}
	}
	
	int getNum() { return primes.size(); }
	int get(int i) { return primes[i]; }
	int prime_count(int mx) { return prime_nums[mx]; }
	int prime_count(int mi, int mx) { return prime_nums[mx] - prime_nums[mi - 1]; }
};
