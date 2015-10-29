#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// bellman ford
template< typename COST >
class BellmanFord {
private:
	struct Edge {
		int to; COST cost;
		Edge(int to_, COST cost_) : to(to_), cost(cost_) {}
	};
	
	int V;
	Matrix< Edge > edges;
	Vec< COST > dist;
	Vec< int > prev;
	
public:
	BellmanFord(int n) : V(n), edges(n) {}
	
	void addEdge(int from, int to, COST cost) {
		edges[from].push_back(Edge(to, cost));
	}
	
	bool shortestPath(int s) {
		dist.assign(V, (COST)iINF);
		dist[s] = COST(0);
		prev.assign(V, -2);
		bool negative = 0;
		
		for_(k,0,V) {
			for_(v,0,V) {
				for (cauto& e : edges[v]) {	
					if (dist[e.to] > dist[v] + e.cost) {
						dist[e.to] = dist[v] + e.cost;
						prev[e.to] = v;
						
						if (k == V - 1) {
							dist[e.to] = COST(-iINF);
							negative = 1;
						}
					}
				}
			}
		}
		
		return negative;
	}
	
	COST getCost(int t) {
		return dist[t];
	}
	
	Vec< int > buildPath(int t) {
		Vec< int > path;
		for (int u = t; u >= 0; u = prev[u]) path.push_back(u);
		reverse(allof(path));
		return path;
	}
};