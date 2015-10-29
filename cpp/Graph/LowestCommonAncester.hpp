#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// lowest common ancester
class LowestCommonAncester {
public:
	struct Result {
		vector< int > depth;
		
		int K;
		vector< vector< int > > parent;
		
		int getLCA(int u, int v) {
			if (depth[u] > depth[v]) swap(u, v);
			
			for_(k,0,K) if ((depth[v] - depth[u]) >> k & 1) v = parent[v][k];
			
			if (u == v) return u;
			
			for_rev(k,K-1,0) {
				if (parent[u][k] != parent[v][k]) {
					u = parent[u][k];
					v = parent[v][k];
				}
			}
			
			return parent[u][0];
		}
	};
	
private:
	int N;
	const vector< vector< int > >& adj;
	
	vector< int > depth;
	vector< vector< int > > parent;
	
	void depthDfs(int v, int p) {
		depth[v] = (p == -1) ? 0 : depth[p] + 1;
		parent[v][0] = p;
		for (int u : adj[v]) if (u != p) depthDfs(u, v);
	}
	
public:
	LowestCommonAncester(const vector< vector< int > >& _adj_) : N(_adj_.size()), adj(_adj_) {}
	
	Result generate(int root) {
		depth.assign(N, 0);
		
		int S = 1, K = 1;
		for (; S < N; S <<= 1) ++K;
		
		parent.assign(N, vector< int >(K, -1));
		
		depthDfs(root, -1);
		
		for_(k,0,K-1) for_(v,0,N) {
			if (parent[v][k] < 0) parent[v][k + 1] = -1;
			else parent[v][k + 1] = parent[ parent[v][k] ][k];
		}
		
		return Result{depth, K, parent};
	}
};