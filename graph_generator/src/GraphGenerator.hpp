#pragma once

#include "GraphData.hpp"
#include "UnionFind.hpp"
#include "XorShift.hpp"

// 0-index で "連結で単純な" グラフを作る
class GraphGenerator {
	XorShift rnd;
	
public:
	GraphGenerator() {}

	GraphData completeGraph(int n);		 // n 頂点の完全グラフ
	GraphData gridGraph(int X, int Y);	 // X * Y 頂点のグリッドグラフ	
	GraphData kBranchTree(int k, int h); // 各頂点からの分岐数 k、 高さ h の木
	GraphData bunchGraph(int med);		 // 頂点数 med+2、頂点 0 と {1,...,med} の間、および {1,..,med} と頂点 med+1 の間に辺がある	
	GraphData randomGraph(int n, int m); // n 頂点 m 辺からなるランダムグラフ
};

// 以下実装
GraphData GraphGenerator::completeGraph(int n) {
	int m = n * (n-1) / 2;
	GraphData graph{n, m};
	for (int u=0; u<n; ++u) for (int v=u+1; v<n; ++v) graph.addEdge(u, v);
	return graph;
}

GraphData GraphGenerator::gridGraph(int X, int Y) {
	int m = X * (Y-1) + Y * (X-1);
	GraphData graph{X * Y, m};
	auto getID = [&](int x, int y) { return y * X + x; };
	for (int y=0; y<Y; ++y) for (int x=0; x<X; ++x) {
		if (x < X-1) graph.addEdge(getID(x, y), getID(x+1,y));
		if (y < Y-1) graph.addEdge(getID(x, y), getID(x, y+1));
	}
	return graph;
}

GraphData GraphGenerator::kBranchTree(int k, int h) {
	int n = 0, add = 1;
	for (int i=0; i<=h; ++i) n += add, add *= k;
	GraphData graph{n, n-1};
	int parent = 0, id = 1, branch = k;
	for (int i=1; i<=h; ++i) {
		for (int j=1; j<=branch; ++j) {
			graph.addEdge(parent, id++);
			if (j % k == 0) ++parent;
		}
		branch *= k;
	}
	return graph;
}

GraphData GraphGenerator::bunchGraph(int med) {
	int n = med + 2, m = 2 * med;
	GraphData graph{n, m};
	for (int v=1; v<=med; ++v) graph.addEdge(0, v);
	for (int v=1; v<=med; ++v) graph.addEdge(v, med+1);
	return graph;
}

GraphData GraphGenerator::randomGraph(int n, int m) {
	assert(m >= n-1);
	assert(n * (n-1) / 2 >= m);
	
	typedef std::pair< int, int > pii;
	std::set< pii > edge_set;
	auto invalid = [&](int u, int v) { return (u == v) || edge_set.count(pii(u, v)) || edge_set.count(pii(v, u)); };
	
	GraphData graph{n, m};
	UnionFind uf(n);
	auto addEdge = [&](int u, int v) {
		edge_set.insert(pii(u, v));
		graph.addEdge(u, v);
		uf.unionSet(u, v);
	};
	
	int add_count = 0;
	while (add_count < n-1) {
		int u = rnd.nextUInt(n), v = rnd.nextUInt(n);
		if (invalid(u, v) || uf.sameSet(u, v)) continue;
		addEdge(u, v);
		++add_count;
	}
	
	int rem_count = m - add_count;
	while (rem_count > 0) {
		int u = rnd.nextUInt(n), v = rnd.nextUInt(n);
		if (invalid(u, v)) continue;
		addEdge(u, v);
		--rem_count;
	}
	return graph;
}
