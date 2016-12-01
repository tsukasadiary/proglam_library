#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

class EnumBridge {
private:
	int n;
	Vec< Vec< int > > adj;
	
public:
	EnumBridge(int __n) : n(__n), adj(__n, Vec< int >()) {}
	
	void addEdge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	void dfs(int v, int p, int& cnt, Vec< int >& pos, Vec< int >& link, Vec< pii >& bridge) {
		if (pos[v] != -1) {
			link[p] = min(link[p], pos[v]);
			return;
		}
				
		pos[v] = link[v] = cnt; ++cnt;
		
		for (int u : adj[v]) {
			if (u == p) continue;
			dfs(u, v, cnt, pos, link, bridge);
			link[v] = min(link[v], link[u]);
		}
		
		if (p != -1 && pos[v] == link[v]) bridge.push_back(pii(min(p, v), max(p, v)));
	}
	
	Vec< pii > run() {
		Vec< pii > res;
		int cnt = 0;
		Vec< int > pos(n, -1);
		Vec< int > link(n, n);
		for_(v,0,n) dfs(v, -1, cnt, pos, link, res);
		return res;
	}
};
