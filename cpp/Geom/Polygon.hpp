#include "GeometoryBase.hpp"

// 多角形構造体
struct Polygon {
	Vec< Point > vert;
	Polygon(int n = 3) : vert(n, Point(0, 0)) {}
	
	Double area() const {
		Double res = 0;
		int v_size = size();
		
		for_(i,0,v_size) res += cross(at(i), at(i+1));
		
		return fabs(res) / 2.;
	}
	
	Point at(int i) const {
		i %= size();
		return vert[i];
	}
	
	int size() const { return size_of(vert); }
};

// 点の内包判定
enum { IN, ON, OUT };
int point_in_poly(const Polygon& g, const Point& p) {
	bool in = false;
	int n = size_of(g);
	
	for_(i,0,n) {
		Point a = g.at(i) - p, b = g.at(i + 1) - p;
		if (a.y > b.y) swap(a, b);
		if (a.y <= 0 && 0 < b.y && cross(a, b) + EPS < 0) in = !in;
		if (fabs(cross(a, b)) < EPS && dot(a, b) <= 0) return ON;
	}
	
	return in ? IN : OUT;
}

// 凸包
Polygon convex_hull(Vec< Point > vp) {
	int n = size_of(vp), k = 0;
	sort(allof(vp));
	Vec< Point > ch(2 * n, Point(0, 0));
	
	for (int i = 0; i < n; ch[k++] = vp[i++]) {
		while (k >= 2 && ccw(ch[k - 2], ch[k - 1], vp[i]) <= 0) --k;
	}
	
	for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = vp[i--]) {
		while (k >= t && ccw(ch[k - 2], ch[k - 1], vp[i]) <= 0) --k;
	}
	
	Polygon res(k - 1);
	for_(i,0,k-1) res.vert[i] = ch[i];
	return res;
}

// 最遠点対間距離
pair< pii, Double > caliper(const Polygon& p) {
	int i = 0, j = 0;
	for_(k,0,p.size()) {
		if (!(p.at(i) < p.at(k))) i = k;
		if (p.at(j) < p.at(k)) j = k;
	}
	
	pii pp(-1, -1);
	Double res = 0;
	
	int si = i, sj = j;
	while (i != sj || j != si) {
		Double cur = abs(p.at(i) - p.at(j));
		
		if (res + EPS < cur) {
			res = cur;
			pp = pii(i, j);
		}
		
		if (cross(p.at(i + 1) - p.at(i), p.at(j + 1) - p.at(j)) < 0) ++i;
		else ++j;
	}
	
	return make_pair(pp, res);
}