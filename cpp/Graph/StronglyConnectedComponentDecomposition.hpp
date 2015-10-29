#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// Strongly Connected Component Decomposition
class StronglyConnectedComponentDecomposition {
public:
	struct Result {
		Vec< int > topol;
		Vec< Vec< int > > dag;
	};
	
private:
	int N;
	const Vec< Vec< int > >& adj;
	Vec< Vec< int > > rev_adj;
	
	Vec< int > rev_order;
	Vec< bool > used;	
	Vec< int > topol;
	
	void dfs(int v) {
		used[v] = true;
		for (int u : adj[v]) if (!used[u]) dfs(u);
		rev_order.push_back(v);
	}
	
	void revDfs(int v, int k) {
		used[v] = true;
		topol[v] = k;
		for (int u : rev_adj[v]) if (!used[u]) revDfs(u, k);
	}
	
public:
	StronglyConnectedComponentDecomposition(const Vec< Vec< int > >& _adj_) : N(_adj_.size()), adj(_adj_) {
		rev_adj.assign(N, Vec< int >());
		for_(v,0,N) for (int u : adj[v]) rev_adj[u].push_back(v);
	}
	
	Result decomposition() {
		used.assign(N, false);
		rev_order.clear();
		topol.assign(N, -1);
		
		for_(v,0,N) if (!used[v]) dfs(v);
		
		fill(allof(used), false);
		
		int k = 0, m = rev_order.size();
		
		for_rev(i,m-1,0) {
			int v = rev_order[i];
			if (!used[v]) revDfs(v, k++);
		}
		
		Vec< Vec< int > > dag(k);
		
		for_(v,0,N) {
			int tv = topol[v];
			
			for (int u : adj[v]) {
				int tu = topol[u];
				if (tv != tu) dag[tv].push_back(tu);
			}
		}
		
		for_(i,0,k) {
			sort(allof(dag[i]));
			dag[i].erase(unique(allof(dag[i])), dag[i].end());
		}
		
		return Result{ topol, dag };
	}
};