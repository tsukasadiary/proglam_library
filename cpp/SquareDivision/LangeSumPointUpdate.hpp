#include <vector>
#include <algorithm>

class SquareDivision_LSPU {
private:
	const int BUCKET_SIZE = 256;
	
	int N, B;
	std::vector< int > data, bucket_sum;

public:
	SquareDivision(int N__) {
		B = (N__ + BUCKET_SIZE - 1) / BUCKET_SIZE;
		N = B * BUCKET_SIZE;
		data.assign(N, 0);
		bucket_sum.assign(B, 0);
	}
	
	void updateQuery(int i, int x) {
		int j = i / BUCKET_SIZE;// i in bucket j
		bucket_sum[j] += (x - data[i]);
		data[i] = x;
	}
	
	int sumQuery(int l, int r) { // [l,r)
		int sum = 0;
		for (int i=0; i<B; ++i) {
			int s = i * BUCKET_SIZE;
			int t = s + BUCKET_SIZE; // bucket i: [s,t)
			if (t <= l || r <= s) continue; // ignored
			else if (l <= s && t <= r) sum += bucket_sum[i]; // A
			else for (int j=std::max(s,l); j<std::min(t,r); ++j) sum += data[j]; // B
		}
		return sum;
	}
};

