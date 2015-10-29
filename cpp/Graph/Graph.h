#ifndef GRAPH_H
#define GRAPH_H

#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

#include "DataStructure.h"

/*** Graph ***/

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

// warshall floyd
template< typename COST >
class WarshallFloyd {
private:
	int V;
	Matrix< COST > dist;
	Matrix< int > inter;
	
public:
	WarshallFloyd(int n) : V(n), dist(n, Vec< COST >(n, (COST)iINF)) {}
	
	void addEdge(int from, int to, COST cost) {
		dist[from][to] = cost;
	}
	
	void shortestPath() {
		inter.assign(V, Vec< int >(V, -1));
		
		for_(k,0,V) for_(i,0,V) for_(j,0,V) {
			if (dist[i][j] > dist[i][k] + dist[k][j]) {
				dist[i][j] = dist[i][k] + dist[k][j];
				inter[i][j] = k;
			}
		}
	}
	
	COST getCost(int s, int t) {
		return dist[s][t];
	}
	
	void buldPath(int s, int t, Vec< int >& path) {
		int u = inter[s][t];
		
		if (u < 0) {
			path.push_back(s);
		} else {
			buildPath(s, u, path);
			buildPath(u, t, path);
		}
	}
	
	Vec< int > buildPath(int s, int t) {
		Vec< int > path;
		buildPath(s, t, path);
		path.push_back(t);
		return path;
	}
};

// minimum spanning tree --- kruskal
template< typename COST >
class MinimumSpanningTree {
private:
	struct Edge {
		int from, to; COST cost;
		Edge(int from_, int to_, COST cost_)
		: from(from_), to(to_), cost(cost_) {}
		bool operator < (const Edge& a) const { return cost < a.cost; }
	};
	
	int V;
	Vec< Edge > edges;
	
public:
	MinimumSpanningTree(int n) : V(n) {}
	
	void addEdge(int from, int to, COST cost) {
		edges.push_back(from, to, cost);
	}
	
	COST getMinCost() {
		sort(allof(edges));
		
		UnionFind uf(V);
		COST res = COST();
		
		for (cauto& e : edges) {
			if (!uf.sameSet(e.from, e.to)) {
				uf.unionSet(e.from, e.to);
				res += e.cost;
			}
		}
		
		return res;
	}
};

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

// min cost flow --- PrimelDual
template< typename FLOW, typename COST >
class PrimalDual {
private:
	typedef pair< COST, int > pci;
	static const COST cINF = COST(iINF);
	
	struct Edge {
		int to, rev; FLOW cap; COST cost;
		Edge(int to_, int rev_, FLOW cap_, COST cost_)
		: to(to_), rev(rev_), cap(cap_), cost(cost_) {}
	};
	
	int V;
	Matrix< Edge > edges;
	Vec< COST > pot, cost;
	Vec< int > prevv, preve;
	
public:
	PrimalDual(int n) : V(n), edges(n), pot(n, COST()),
						cost(n, COST()), prevv(n, -1), preve(n, -1) {}
	
	void addEdge(int from, int to, FLOW cap, COST cost) {
		edges[from].push_back(Edge(to, size_of(edges[to]), cap, cost));
		edges[to].push_back(Edge(from, size_of(edges[from]) - 1, FLOW(), -cost));
	}
	
	COST minCostFlow(int s, int t, FLOW f) {
		COST res = COST();
		fill(allof(pot), 0);
		
		while (f > 0) {
			// bellman ford ver
			/*
			fill(allof(cost), cINF);
			cost[s] = COST();
			bool update = 1;
			
			while (update) {
				update = 0;
				
				for_(v,0,V) {
					if (cost[v] == cINF) continue;
					
					int edge_nums = size_of(edges[v]);
					for_(i,0,edge_nums) {
						Edge& e = edges[v][i];
						
						if (e.cap > 0 && cost[e.to] > cost[v] + e.cost) {
							cost[e.to] = cost[v] + e.cost;
							prevv[e.to] = v;
							preve[e.to] = i;
							update = 1;
						}
					}
				}
			}
			*/
			// bellman ford ver
			
			// dijkstra ver
			priority_queue< pci, Vec< pci >, greater< pci > > que;
			fill(allof(cost), cINF);
			cost[s] = COST();
			que.push(pci(COST(), s));
			
			while (!que.empty()) {
				pci p = que.top(); que.pop();
				int v = p.second;
				
				if (cost[v] < p.first) continue;
				
				int edge_nums = size_of(edges[v]);
				for_(i,0,edge_nums) {
					Edge& e = edges[v][i];
					if (e.cap > 0 && cost[e.to] > cost[v] + e.cost + pot[v] - pot[e.to]) {
						cost[e.to] = cost[v] + e.cost + pot[v] - pot[e.to];
						prevv[e.to] = v;
						preve[e.to] = i;
						que.push(pci(cost[e.to], e.to));
					}
				}
			}
			// dijkstra ver
			
			if (cost[t] == cINF) return COST(-1);
			
			for_(i,0,V) pot[i] += cost[i];
			
			FLOW d = f;
			for (int u = t; u != s; u = prevv[u]) d = min(d, edges[prevv[u]][preve[u]].cap);
			f -= d;			
			res += (COST)d * pot[t];
			
			// bellman ford ver
			//res += d * cost[t];
			
			for (int u = t; u != s; u = prevv[u]) {
				Edge& e = edges[prevv[u]][preve[u]];
				e.cap -= d;
				edges[u][e.rev].cap += d;
			}
		}
			
		return res;
	}
};

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

#endif // GRAPH_H