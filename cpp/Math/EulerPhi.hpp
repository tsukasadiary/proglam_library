int eulerPhi(int n) {
	int res = n;
	
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			res = res / i * (i - 1);
			for (; n % i == 0; n /= i);
		}
	}
	
	if (n != 1) res = res / n * (n - 1);
	return res;
}

Vec< int > eulerPhi(int MAX_N) {
	Vec< int > res(MAX_N);
	for_(i,0,MAX_N) res[i] = i;
	
	for (int i = 2; i < MAX_N; ++i) {
		if (res[i] == i) {
			for (int j = i; j < MAX_N; j +=i ) res[i] = res[i] / i * (i - 1);
		}
	}
	
	return res;
}
