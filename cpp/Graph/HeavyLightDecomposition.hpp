#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// Heavy Light Decomposition
class HeavyLightDecomposition {
public:
	#define __HLD_WITH_STACK__
	
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
		#ifndef __HLD_WITH_STACK__
		int part = 1;
		
		for (int u : adj[v]) {
			if (u != p) {
				int nxt = partDfs(u, v);
				maxUpdate(part_max[v], pii(nxt, u));
				part += nxt;
			}
		}
		
		return part;
		#else
		stack< pii > nst; nst.push(pii(v, p));
		stack< int > cst;
		
		while (!nst.empty()) {
			pii var = nst.top(); nst.pop();
			v = var.first; p = var.second;
			
			if (v < N) {
				nst.push(pii(v + N, p));
				cst.push(1);
				for (int u : adj[v]) if (u != p) nst.push(pii(u, v));
			} else if (p != -1) {
				int c = cst.top(); cst.pop();
				maxUpdate(part_max[p], pii(c, v - N));
				int nc = cst.top(); cst.pop();
				cst.push(c + nc);
			}
		}
		
		return cst.top();
		#endif
	}
	
	void decompDfs(int v, int p) {	
		#ifndef __HLD_WITH_STACK__	
		vinfo[v].nodeID = nodes.size() - 1;
		vinfo[v].pos = nodes[ nodes.size() - 1 ].path.size();
		
		nodes[ nodes.size() - 1 ].path.push_back(v);
		
		if (part_max[v].second != -1) {
			decompDfs(part_max[v].second, v);
			
			for (int u : adj[v]) {
				if (u != p && u != part_max[v].second) {
					nodes[ vinfo[v].nodeID ].adj.push_back(nodes.size());
					nodes.push_back(Node{v, vector< int >(), vector< int >()});
					
					decompDfs(u, v);
				}
			}
		}
		#else
		stack< pii > nst; nst.push(pii(v, p));
		stack< int > ist; ist.push(0);
		int max_id = 0;
		
		while (!nst.empty()) {
			pii var = nst.top(); nst.pop();
			int v = var.first, p = var.second;
			int nid = ist.top(); ist.pop();
			
			vinfo[v].nodeID = nid;
			vinfo[v].pos = nodes[nid].path.size();
			
			nodes[nid].path.push_back(v);
							
			if (part_max[v].second != -1) {
				nst.push(pii(part_max[v].second, v));
				ist.push(nid);
				
				for (int u : adj[v]) {
					if (u != p && u != part_max[v].second) {
						nodes[nid].adj.push_back(++max_id);
						nodes.push_back(Node{v, vector< int >(), vector< int >()});
						
						nst.push(pii(u, v));
						ist.push(max_id);
					}
				}
			}
		}
		#endif
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
