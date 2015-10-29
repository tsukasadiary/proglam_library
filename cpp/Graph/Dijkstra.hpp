#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// dijkstra
template< typename COST >
class Dijkstra {
private:
	struct Edge {
		int from, to; COST cost;
		
		Edge(int from_, int to_, COST cost_)
		: from(from_), to(to_), cost(cost_) {}
		
		bool operator > (const Edge& a) const { return cost > a.cost; }
	};
	
	int V;
	Matrix< Edge > edges;
	Vec< COST > dist;
	Vec< int > prev;
	
public:
	Dijkstra(int n) : V(n), edges(n) {}
	
	void addEdge(int from, int to, COST cost) {
		edges[from].push_back(Edge(from, to, cost));
	}
	
	void shortestPath(int s) {
		dist.assign(V, (COST)iINF);
		dist[s] = COST(0);
		prev.assign(V, -1);
		priority_queue< Edge, Vec< Edge >, greater< Edge > > que;
		que.push(Edge(-2, s, 0));
		
		while (!que.empty()) {
			Edge e = que.top(); que.pop();
			if (prev[e.to] != -1) continue;
			prev[e.to] = e.from;
			
			for (cauto& ei : edges[e.to]) {
				if (dist[ei.to] > e.cost + ei.cost) {
					dist[ei.to] = e.cost + ei.cost;
					que.push(Edge(ei.from, ei.to, dist[ei.to]));
				}
			}
		}
	}
	
	COST getCost(int t) {
		return dist[t];
	}
	
	Vec< int > builtPath(int t) {
		Vec< int > path;
		for (int u = t; u >= 0; u = prev[u]) path.push_back(u);
		reverse(allof(path));
		return path;
	}
};