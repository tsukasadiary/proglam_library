#include <vector>
#include <algorithm>

class SquareDivision_LSLU {
private:
	const int BUCKET_SIZE = 256;
	
	int N, B;
	std::vector< int > data, bucket_sum;
	std::vector< bool > bucket_flag;

public:
	SquareDivision_Lazy(int N__) {
		B = (N__ + BUCKET_SIZE - 1) / BUCKET_SIZE;
		N = B * BUCKET_SIZE;
		data.assign(N, 0);
		bucket_sum.assign(B, 0);
		bucket_flag.assign(B, false);
	}
	
	void lazyUpdate(int i) { // for bucket i
		if (bucket_flag[i]) {
			int s = i * BUCKET_SIZE;
			int t = s + BUCKET_SIZE;
			for (int j=s; j<t; ++j) data[j] = bucket_sum[i] / BUCKET_SIZE;
			bucket_flag[i] = false;
		}
	}
	
	void updateQuery(int l, int r, int x) { // [l,r)
		for (int i=0; i<B; ++i) {
			int s = i * BUCKET_SIZE;
			int t = s + BUCKET_SIZE; // bucket i: [s,t)
			if (t <= l || r <= s) continue; // ignored
			else if (l <= s && t <= r) { // A
				bucket_sum[i] = BUCKET_SIZE * x;
				bucket_flag[i] = true;
			}
			else { // B
				lazyUpdate(i);
				for (int j=std::max(s,l); j<std::min(t,r); ++j) data[j] = x;
				bucket_sum[i] = 0;
				for (int j=s; j<t; ++j) bucket_sum[i] += data[j];
			}
		}
	}
	
	int sumQuery(int l, int r) { // [l,r)
		int sum = 0;
		for (int i=0; i<B; ++i) {
			int s = i * BUCKET_SIZE;
			int t = s + BUCKET_SIZE; // bucket i: [s,t)
			if (t <= l || r <= s) continue; // ignored
			else if (l <= s && t <= r) sum += bucket_sum[i]; // A
			else { // B
				lazyUpdate(i);
				for (int j=std::max(s,l); j<std::min(t,r); ++j) sum += data[j];
			}
		}
		return sum;
	}
};
