#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

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
