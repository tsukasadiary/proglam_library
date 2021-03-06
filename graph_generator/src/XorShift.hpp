#pragma once

struct XorShift {
	unsigned int x, y, z, w;
	
	XorShift() { init(); }
	XorShift(unsigned int seed) { init(seed); }
	
	void init(unsigned int seed = 88675123) { x = 123456789; y = 362436069; z = 521288629; w = seed; }
	
	void setNext() {
		unsigned int t = x ^ (x << 11);
		x = y; y = z; z = w;
		w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	}
	
	unsigned int nextUInt(unsigned int n) {
		setNext();
		return w % n;
	}

	unsigned int nextUInt() {
		setNext();
		return w;
	}

	double nextDouble() {
		unsigned int i = nextUInt();
		return i * (1.0 / 0xFFFFFFFFu);
	}
};
