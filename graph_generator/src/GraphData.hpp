#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <cassert>
#include <set>
#include <map>

// 辺データを保持
struct EdgeData {
	int u, v;
};

// グラフデータを保持
struct GraphData {
public:
	int n, m;
	std::vector< EdgeData > edge;
	
	EdgeData& operator [] (int i) { return edge[i]; } // i 番目の辺を取得
	
	void addEdge(int u, int v) { edge.push_back(EdgeData{u, v}); }
	
	void dump(std::ostream& os) const { // グラフを競プロ的フォーマットで出力、 os で出力先を指定
		os << n << " " << m << std::endl;
		for (const EdgeData& e : edge) os << e.u << " " << e.v << std::endl;
	}
	
	void shuffleID() { // グラフの形を変えずに頂点番号をランダムに付け替える
		std::vector< int > trans(n);
		std::iota(trans.begin(), trans.end(), 0);
		shuffle(trans.begin(), trans.end(), std::mt19937());
		for (EdgeData& e : edge) e.u = trans[e.u], e.v = trans[e.v];
	}
	
	void shuffleEdge() { // 辺の順序をランダムに変える
		shuffle(edge.begin(), edge.end(), std::mt19937());
	}
};
