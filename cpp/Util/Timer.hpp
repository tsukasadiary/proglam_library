#include "../template.hpp"
#include <sys/time.h>

struct Timer {
	struct timeval start, cur;
	double limit;
	
	Timer() : limit(0) { gettimeofday(&start, NULL); }
	Timer(double l) : limit(l) { gettimeofday(&start, NULL); }
	
	bool isLimit() { return curTime() > limit; }
	
	double curTime() {
		gettimeofday(&cur, NULL);
		return (cur.tv_sec - start.tv_sec) + (cur.tv_usec - start.tv_usec) / 1e6;
	}
};
