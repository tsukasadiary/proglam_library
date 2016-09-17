#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

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
