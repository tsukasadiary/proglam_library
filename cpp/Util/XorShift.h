#ifndef XOR_SHIFT_H
#define XOR_SHIFT_H

struct XorShift {
	uint32_t x, y, z, w;
	
	XorShift() {
		init();
	}
	
	XorShift(uint32_t seed) {
		init(seed);
	}
	
	void init(uint32_t seed = 88675123) {
		x = 123456789;
		y = 362436069;
		z = 521288629;
		w = seed;		
	}
	
	uint32_t nextUInt(uint32_t n) {
		uint32_t t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
		return w % n;
	}

	uint32_t nextUInt() {
		uint32_t t = x ^ (x << 11);
		x = y;
		y = z;
		z = w;
		return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}

	double nextDouble() {
		uint32_t i = nextUInt();
		return i * (1.0 / 0xFFFFFFFFu);
	}
};

#endif