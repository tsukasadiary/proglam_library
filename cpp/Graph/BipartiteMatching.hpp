#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// bipartite matching
class BipartiteMatching {
private:
	int V;
	Vec< Vec< int > > adj;
	Vec< int > match;
	Vec< bool > used;
	
public:
	BipartiteMatching(int n_) : V(n_), adj(n_, Vec< int >()), match(n_, -1), used(n_, 0) {}
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	bool dfs(int v) {
		used[v] = 1;
		
		for (cauto& u : adj[v]) {
			int w = match[u];
			
			if (w < 0 || (!used[w] && dfs(w))) {
				match[v] = u;
				match[u] = v;
				return 1;
			}
		}
		
		return 0;
	}
	
	int bipMatch() {
		int res = 0;
		fill(allof(match), -1);
		
		for_(v,0,V) {
			if (match[v] < 0) {
				fill(allof(used), 0);
				if (dfs(v)) ++res;
			}
		}
		
		return res;
	}
};