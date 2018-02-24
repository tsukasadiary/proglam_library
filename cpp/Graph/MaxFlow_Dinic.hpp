#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// max flow --- Dinic
template< typename FLOW > class Dinic {
private:
	struct Edge { int to; FLOW cost; int rev; };
	
	int n;
	Vec< Vec< Edge > > edge;
	Vec< int > level, iter;
	
public:
	Dinic(int n_) : n(n_), edge(n_), level(n_, -1), iter(n_, 0) {}
	
	void addEdge(int from, int to, FLOW cost) {
		edge[from].push_back(Edge{to, cost, (int)edge[to].size()});
		edge[to].push_back(Edge{from, FLOW(), (int)edge[from].size() - 1});
	}
	
	void bfs(int s) {
		level.assign(n, -1);
		queue< int > que; que.push(s);
		level[s] = 0;		
		while (!que.empty()) {
			int v = que.front(); que.pop();
			for (const Edge& e : edge[v]) {
				if (e.cost > 0 && level[e.to] < 0) {
					level[e.to] = level[v] + 1;
					que.push(e.to);
				}
			}
		}
	}
	
	FLOW dfs(int v, int t, FLOW f) {
		if (v == t) return f;
		for (int& i = iter[v]; i < (int)edge[v].size(); ++i) {
			Edge& e = edge[v][i];
			if (e.cost > 0 && level[v] < level[e.to]) {
				FLOW d = dfs(e.to, t, min(f, e.cost));
				if (d > 0) {
					e.cost -= d;
					edge[e.to][e.rev].cost += d;
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
			iter.assign(n, 0);
			FLOW fl;
			while ((fl = dfs(s, t, FLOW(1e9))) > 0) f += fl;
		}
	}
};
