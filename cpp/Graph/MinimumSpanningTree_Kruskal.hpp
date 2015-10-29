#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

#include "../UnionFind.hpp"

// minimum spanning tree --- kruskal
template< typename COST >
class MinimumSpanningTree {
private:
	struct Edge {
		int from, to; COST cost;
		Edge(int from_, int to_, COST cost_)
		: from(from_), to(to_), cost(cost_) {}
		bool operator < (const Edge& a) const { return cost < a.cost; }
	};
	
	int V;
	Vec< Edge > edges;
	
public:
	MinimumSpanningTree(int n) : V(n) {}
	
	void addEdge(int from, int to, COST cost) {
		edges.push_back(from, to, cost);
	}
	
	COST getMinCost() {
		sort(allof(edges));
		
		UnionFind uf(V);
		COST res = COST();
		
		for (cauto& e : edges) {
			if (!uf.sameSet(e.from, e.to)) {
				uf.unionSet(e.from, e.to);
				res += e.cost;
			}
		}
		
		return res;
	}
};