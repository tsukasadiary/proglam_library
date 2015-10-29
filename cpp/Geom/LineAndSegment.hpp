#include "GeometoryBase.hpp"

// 直線、線分構造体
typedef struct Line {
	Point s, e;
	Line(Point s_, Point e_) : s(s_), e(e_) {}
} Segment;

// 線分の交差判定
bool is_cross(const Segment& a, const Segment& b) {
	return (ccw(a.s, a.e, b.s) * ccw(a.s, a.e, b.e) <= 0
			&& ccw(b.s, b.e, a.s) * ccw(b.s, b.e, a.e) <= 0);
}
// 直線の平衡判定
bool is_parrallel(const Line& a, const Line& b) {
	return is_parrallel(a.s - a.e, b.s - b.e);
}

/*** distance ***/
// 点と線の距離
Double dist_point_line(const Point& p, const Line& l) {
	return fabs(cross(p - l.s, l.e - l.s)) / abs(l.e - l.s);
}

// 点と線分の距離
Double dist_point_seg(const Point& p, const Segment& s) {
	if (dot(s.e - s.s, p - s.s) < EPS) return abs(p - s.s);
	if (dot(s.s - s.e, p - s.e) < EPS) return abs(p - s.e);
	return dist_point_line(p, s);
}

// 線分と線分の距離
Double dist_seg_seg(const Segment& a, const Segment& b) {
	if (is_cross(a, b)) return 0.;
	Double res = dist_point_seg(b.s, a);
	res = min(res, dist_point_seg(b.e, a));
	res = min(res, dist_point_seg(a.s, b));
	res = min(res, dist_point_seg(a.e, b));
	return res;
}

// 直線の交点
Point cross_point(const Line& a, const Line& b) {
	Double d1 = cross(b.e - b.s, b.s - a.s);
	Double d2 = cross(b.e - b.s, a.e - a.s);
	return a.s + (a.e - a.s) * d1 / d2;
}

// 点の直線上判定
bool point_on_line(const Point& p, const Line& l) {
	return ( (ccw(l.s, l.e, p) + 2) % 2 == 0 );
}

// 点の線分上判定
bool point_on_seg(const Point& p, const Segment& s) {
	return (ccw(s.s, s.e, p) == 0);
}

// line symmetry point
Point symmetry_point(const Point& p, const Line& l) {
	Vector b = p - l.s, c = l.e - l.s, a = b - c;
	double s = angle(abs(a), abs(b), abs(c));
	return l.s + rotate(b, 2 * s);
}