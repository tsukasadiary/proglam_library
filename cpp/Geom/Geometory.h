#ifndef GEOMETORY_H
#define GEOMETORY_H

#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

/*** Geometory ***/

// 点、ベクトル構造体
typedef struct Point {
	Double x, y;
	Point(Double x_, Double y_) : x(x_), y(y_) {}
	
	bool operator < (const Point& a) const {
		return fabs(x - a.x) < EPS ? y + EPS < a.y : x + EPS < a.x;
	}
	
	bool operator > (const Point& a) const {
		return a < *this;
	}
	
	bool operator == (const Point& a) const {
		return !(a < *this) && !(a > *this);
	}
	
	Point operator + (const Point& a) const {
		return Point(x + a.x, y + a.y);
	}
	
	Point operator - (const Point& a) const {
		return Point(x - a.x, y - a.y);
	}
	
	Point operator * (const Point& a) const {
		return Point(x * a.x, y * a.y);
	}
	
	Point operator / (const Point& a) const {
		return Point(x / a.x, y / a.y);
	}
	
	Point operator * (const Double& d) const {
		return Point(x * d, y * d);
	}
	
	Point operator / (const Double& d) const {
		return Point(x / d, y / d);
	}
} Vector;

// ノルム
Double norm(const Point& a) {
	return a.x * a.x + a.y * a.y;
}
// サイズ
Double abs(const Point& a) {
	return sqrt(norm(a));
}
// 内積
Double dot(const Vector& a, const Vector& b) {
	return a.x * b.x + a.y * b.y;
}
// 外積
Double cross(const Vector& a, const Vector& b) {
	return a.x * b.y - a.y * b.x;
}
// 距離
Double distance(const Point& a, const Point& b) {
	return abs(a - b);
}
// 直行判定
bool is_vertical(const Vector& a, const Vector& b) {
	return fabs(dot(a, b)) < EPS;
}
// 平衡判定
bool is_parrallel(const Vector& a, const Vector& b) {
	return fabs(cross(a, b)) < EPS;
}

// 単位ベクトル
Vector unit_vector(const Vector& a) {
	return a / abs(a);
}
// 法線ベクトル
pair<Vector, Vector> normal_vectors(const Vector& a) {
	return make_pair(Vector(a.y, -a.x), Vector(-a.y, a.x));
}
// 単位法線ベクトル
pair<Vector, Vector> normal_unit_vectors(const Vector& a) {
	return make_pair(unit_vector( Vector(a.y, -a.x) ), unit_vector( Vector(-a.y, a.x) ));	
}

// ベクトルa,bのなす角のサイン値
Double sign(const Vector& a, const Vector& b) {
	return cross(a, b) / (abs(a) * abs(b));
}
// ベクトルa,bのなす角のコサイン値
Double cosign(const Vector& a, const Vector& b) {
	return dot(a, b) / (abs(a) * abs(b));
}

// 三角形の辺B,C間の角度
Double angle(Double _a, Double _b, Double _c) {
	return acos((_b * _b + _c * _c - _a * _a) / (2.0 * _b * _c));
}

// 回転
Point rotate(const Vector& v, Double s) {
	return Vector(v.x * cos(s) - v.y * sin(s),
				  v.x * sin(s) + v.y * cos(s));
}

// 三角形の面積
Double area_of_tri(const Point& a, const Point& b, const Point& c) {
	Vector ac = a - c, bc = b - c;
	return cross(ac, bc) / 2.;
}

// counter clockwise
int ccw(const Point& a, const Point& b, const Point&  c) {
	Vector ba = b - a, ca = c - a;
	if (cross(ba, ca) > EPS) return +1; // ccw
	if (cross(ba, ca) < -EPS) return -1; // cw
	if (dot(ba, ca) < -EPS) return +2; // c-a-b
	if (abs(ba) + EPS < abs(ca)) return -2; // a-b-c
	return 0; // a-c-b
}

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

// 矩形構造体
struct Rect {
	Point lt, rb;
	Rect(Point lt_, Point rb_) : lt(lt_), rb(rb_) {}
};

// 矩形の交差判定
bool rect_intersect(const Rect& a, const Rect& b) {
	return (a.lt.x <= b.rb.x && a.rb.y <= b.lt.y && b.lt.x <= a.rb.x && b.rb.y <= a.lt.y);
}

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

#endif // GEOMETORY_H