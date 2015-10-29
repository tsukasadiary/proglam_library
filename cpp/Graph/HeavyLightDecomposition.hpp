#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// Heavy Light Decomposition
class HeavyLightDecomposition {
public:
	struct Node {
		int parent;
		Vec< int > path;
		Vec< int > adj;
	};
	
	struct VertexInfo { int nodeID, pos; };
	
	struct Result {
		Vec< Node > nodes;
		Vec< VertexInfo > vinfo;
		
		int getNodeId(int v) { return vinfo[v].nodeID; }
		int getPathPos(int v) { return vinfo[v].pos; }
	};
	
private:
	int N;
	const Vec< Vec< int > >& adj;
	
	Vec< Node > nodes;
	Vec< VertexInfo > vinfo;
	Vec< pii > part_max;
	
	int partDfs(int v, int p) {
		int part = 1;
		
		for (int u : adj[v]) {
			if (u != p) {
				int nxt = partDfs(u, v);
				maxUpdate(part_max[v], pii(nxt, u));
				part += nxt;
			}
		}
		
		return part;
	}
	
	void decompDfs(int v, int p) {		
		vinfo[v].nodeID = nodes.size() - 1;
		vinfo[v].pos = nodes[ nodes.size() - 1 ].path.size();
		
		nodes[ nodes.size() - 1 ].path.push_back(v);
		
		if (part_max[v].second != -1) {
			decompDfs(part_max[v].second, v);
			
			for (int u : adj[v]) {
				if (u != p && u != part_max[v].second) {
					nodes[ vinfo[v].nodeID ].adj.push_back(nodes.size());
					nodes.push_back(Node{v, Vec< int >(), Vec< int >()});
					
					decompDfs(u, v);
				}
			}
		}
	}
	
public:
	HeavyLightDecomposition(const Vec< Vec< int > >& _adj_) : N(_adj_.size()), adj(_adj_) {}
	
	Result decomposition(int root) {
		part_max.assign(N, pii(-1, -1));
		
		partDfs(root, -1);
		
		nodes.clear();
		nodes.push_back(Node{-1, Vec< int >(), Vec< int >()});
		
		vinfo = Vec< VertexInfo >(N);
		
		decompDfs(root, -1);
		
		return Result{nodes, vinfo};
	}
};