#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.hpp"
#endif

// Euler Tour
class EulerTour {
public:	
	struct Result {
		Vec< int > tour;
		Vec< pii > range;
	};
	
private:
	int N;
	const vector< vector< int > >& adj;
	
	void dfs(int v, int p, int& step, Result& res) {
		res.tour[step] = v;
		res.range[v].first = step++;
		for (int u : adj[v]) {
			if (u != p) {
				dfs(u, v, step, res);
				res.tour[step++] = v;
			}
		}
		res.range[v].second = step;
	}
	
public:
	EulerTour(const vector< vector< int > >& _adj_) : N(_adj_.size()), adj(_adj_) {}
	
	Result generate(int root, bool use_dfs = true) {
		Result res{Vec< int >(2 * N - 1), Vec< pii >(N)};
		
		if (use_dfs) {
			int step = 0;
			dfs(root, -1, step, res);
		} else {
			int step = 0;
			stack< pii > st; st.push(pii(root, -1));
			
			while (!st.empty()) {
				pii pt = st.top(); st.pop();
				int v = pt.first, p = pt.second;
				
				if (p == N) {
					res.range[v].second = step;
				} else if (p == v) {
					res.tour[step++] = v;
				} else {			
					res.tour[step] = v;
					res.range[v].first = step++;
					st.push(pii(v, N));
					
					for (int u : adj[v]) {
						if (u != p) {
							st.push(pii(v, v));
							st.push(pii(u, v));
						}
					}
				}	
			}
		}
		
		return res;
	}
};
