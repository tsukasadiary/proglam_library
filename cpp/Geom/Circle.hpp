#include "GeometoryBase.hpp"

// 円構造体
struct Circle {
	Point c; Double r;
	Circle(Point c_, Double r_) : c(c_), r(r_) {}
	
	Double area() const { return PI * r * r; }
};

// 円の衝突
int circle_intersect(const Circle& a, const Circle& b) {
	Double d = abs(a.c - b.c);
	if (a.r + b.r + EPS < d) return 0; // 0 : outside
	if (b.r + d + EPS < a.r) return -3; // 0 : b in a
	if (a.r + d + EPS < b.r) return -4; // 0 : a in b
	if (fabs(a.r + b.r - d) < EPS) return 1; // 1 : outside
	if (fabs(b.r + d - a.r) < EPS) return 3; // 1 : b in a
	if (fabs(a.r + d - b.r) < EPS) return 4; // 1 : a in b
	return 2; // 2
}

// 2円の交点
Vec<Point> cross_point(const Circle& a, const Circle& b) {
	Vec<Point> res;
	Point x = unit_vector(b.c - a.c) * a.r;
	int ci = circle_intersect(a, b);
	
	if (ci > 0) {
		if (ci != 2) {
			res.push_back(a.c + x);
		} else {
			Double s = angle(b.r, abs(b.c - a.c), a.r);
			res.push_back(a.c + rotate(x, s));
			res.push_back(a.c + rotate(x, -s));
		}
	}
	
	return res;
}

// 円と直線の交点
Vec<Point> cross_point(const Circle& a, const Line& l) {
	Vec<Point> res;
	Point n = normal_vectors(l.s - l.e).first;
	Point p = cross_point(l, Line(a.c, a.c + n));
	
	if (abs( abs(a.c - p) - a.r ) < EPS) {
		res.push_back(p);
	} else if (abs(a.c - p) + EPS < a.r) {
		Double len = sqrt(a.r * a.r - norm(a.c - p));
		Point cp = unit_vector(l.s - l.e) * len;
		res.push_back(p + cp);
		res.push_back(p - cp);
	}
	
	return res;
}

// 2円の共通部分の面積
Double area_of_circle_intersect(const Circle& a, const Circle& b) {
	int ci = circle_intersect(a, b);
	if (ci == 0 || ci == 1) return 0.0;
	if (ci == 3 || ci == -3) return b.area();
	if (ci == 4 || ci == -4) return a.area();
	
	Double d = abs(a.c - b.c);
	Double s1 = angle(b.r, a.r, d), s2 = angle(a.r, b.r, d);
	Double tri = (a.r * a.r * sin(2.0 * s1) + b.r * b.r * sin(2.0 * s2)) / 2.;
	return a.r * a.r * s1 + b.r * b.r * s2 - tri;
}

// 点pから引いた円cの接線
Vec<Line> tangent_line(const Circle& c, const Point& p) {
	Vec<Line> res;
	Point a = c.c + unit_vector(p - c.c) * c.r;
	Vec<Point> b = cross_point( Circle(c.c, abs(c.c - p)),
									Line(a, a + normal_vectors(c.c - p).first) );
	for_(i,0,size_of(b)) {
		res.push_back(Line(p, c.c + unit_vector(b[i] - c.c) * c.r));
	}
	return res;
}

// 2円の共通接線
Vec<Line> common_tangent_line(Circle a, Circle b) {
	Vec<Line> res;
	if (a.c == b.c && fabs(a.r - b.r) < EPS) return res;
	
	if (a.r + EPS < b.r) swap(a, b);
	Point p = (b.c - a.c) * a.r / (a.r + b.r) + a.c;
	
	if (abs(a.c - p) + EPS > a.r) res = tangent_line(a, p);
	
	if (abs(a.r - b.r) < EPS) {
		pair<Point, Point> n = normal_vectors(unit_vector(b.c - a.c) * a.r);
		res.push_back(Line(a.c + n.first, b.c + n.first));
		res.push_back(Line(a.c + n.second, b.c + n.second));
	} else {
		p = (b.c - a.c) * a.r / (a.r - b.r) + a.c;
		if (abs(a.c - p) + EPS > a.r) {
			Vec<Line> tmp = tangent_line(a, p);
			for_(i,0,size_of(tmp)) res.push_back(tmp[i]);
		}
	}
	
	return res;
}