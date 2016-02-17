#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// min cost flow --- PrimelDual
#define __DIJKSTRA__
template< typename FLOW, typename COST >
class PrimalDual {
private:
	typedef pair< COST, int > pci;
	const COST cINF;
	
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
	PrimalDual(int n) : cINF(COST(1e9)), V(n), edges(n), pot(n, COST()),
						cost(n, COST()), prevv(n, -1), preve(n, -1) {}
	
	void addEdge(int from, int to, FLOW cap, COST cost) {
		edges[from].push_back(Edge(to, size_of(edges[to]), cap, cost));
		edges[to].push_back(Edge(from, size_of(edges[from]) - 1, FLOW(), -cost));
	}
	
	COST minCostFlow(int s, int t, FLOW f) {
		COST res = COST();
		fill(allof(pot), 0);
		
		while (f > 0) {
			/** bellman ford ver **/
#ifndef __DIJKSTRA__
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
#else		
			/** dijkstra ver **/
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
#endif
			
			if (cost[t] == cINF) return COST(-1);
			
			for_(i,0,V) pot[i] += cost[i];
			
			FLOW d = f;
			for (int u = t; u != s; u = prevv[u]) d = min(d, edges[prevv[u]][preve[u]].cap);
			f -= d;			
			res += (COST)d * pot[t];

#ifndef __DIJKSTRA__
			res += d * cost[t];
#endif
			
			for (int u = t; u != s; u = prevv[u]) {
				Edge& e = edges[prevv[u]][preve[u]];
				e.cap -= d;
				edges[u][e.rev].cap += d;
			}
		}
			
		return res;
	}
};
