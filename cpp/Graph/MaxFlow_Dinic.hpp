#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// max flow --- Dinic
template< typename FLOW >
class Dinic {
private:
	struct Edge {
		int to; FLOW cost; int rev;
		Edge(int to_, FLOW cost_, int rev_)
		: to(to_), cost(cost_), rev(rev_) {}
	};
	
	int V;
	Matrix< Edge > edges;
	Vec< int > level, iter;
	
public:
	Dinic(int n) : V(n), edges(n), level(n, -1), iter(n, 0) {}
	
	void addEdge(int from, int to, FLOW cost) {
		edges[from].push_back(Edge(to, cost, size_of(edges[to])));
		edges[to].push_back(Edge(from, FLOW(), size_of(edges[from]) - 1));
	}
	
	void bfs(int s) {
		fill(allof(level), -1);
		queue< int > que; que.push(s);
		level[s] = 0;
		
		while (!que.empty()) {
			int v = que.front(); que.pop();
			
			for (cauto& e : edges[v]) {
				if (e.cost > 0 && level[e.to] < 0) {	
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}
	
	FLOW dfs(int v, int t, FLOW f) {
		if (v == t) return f;
		
		int edge_nums = size_of(edges[v]);
		for (int& i = iter[v]; i < edge_nums; ++i) {
			Edge& e = edges[v][i];
			
			if (e.cost > 0 && level[v] < level[e.to]) {
				FLOW d = dfs(e.to, t, min(f, e.cost));
				if (d > 0) {
					e.cost -= d;
					edges[e.to][e.rev].cost += d;
					return d;
				}
			}
		}
		
		return FLOW(-1);
	}
	
	FLOW maxFlow(int s, int t) {
		FLOW f = FLOW();
		
		while (1) {
			bfs(s);
			
			if (level[t] < 0) return f;
			
			fill(allof(iter), 0);
			FLOW fl;
			while ((fl = dfs(s, t, FLOW(iINF))) > 0) f += fl;
		}
	}
};