#ifndef SAFFIX_ARRAY_HPP
#define SAFFIX_ARRAY_HPP

#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "../template.h"
#endif

class SaffixArray {
private:
	const string& text;
	int n, k;
	Vec< int > sa, rank_sf, tmp;
	
	struct CompareSA {
		int &n, &k;
		Vec< int >& rank_sf;
	
		CompareSA(int& _n_, int& _k_, Vec< int >& _rank_sf_)
		: n(_n_), k(_k_), rank_sf(_rank_sf_) {}
		
		bool operator () (const int& i, const int& j) const {
			if (rank_sf[i] != rank_sf[j]) return rank_sf[i] < rank_sf[j];
			int ri = i + k <= n ? rank_sf[i + k] : -1;
			int rj = j + k <= n ? rank_sf[j + k] : -1;
			return ri < rj;
		}
	};
	
	void construct() {
		sa.assign(n + 1, 0);
		rank_sf.assign(n + 1, 0);
		tmp.assign(n + 1, 0);
		
		for_(i,0,n+1) {
			sa[i] = i;
			rank_sf[i] = i < n ? text[i] : -1;
		}
		
		for (k = 1; k <= n; k <<= 1) {
			CompareSA csa(n, k, rank_sf);
			sort(allof(sa), csa);
			tmp[sa[0]] = 0;
			for_(i,1,n+1) tmp[sa[i]] = tmp[sa[i - 1]] + (csa(sa[i - 1], sa[i]) ? 1 : 0);
			for_(i,0,n+1) rank_sf[i] = tmp[i];
		}
	}
	
public:
	SaffixArray(const string& _text_)
	: text(_text_), n(_text_.size()) { construct(); }
	
	int length() const { return n; }
	
	int getSA(int i) const { return sa[i]; }
	
	const string& getText() const { return text; }
	
	int find(const string& p) const {
		int lb = 0, ub = n, m = p.size();
		
		while (ub - lb > 1) {
			int med = (ub + lb) / 2;
			if (text.compare(sa[med], m, p) < 0) lb = med;
			else ub = med;
		}
		
		return text.compare(sa[ub], m, p) == 0 ? sa[ub] : -1;
	}
	
	void dump(ostream& os) const {
		for_(i,0,n+1) {
			os << sa[i] << " " << (sa[i] < n ? text.substr(sa[i]) : "") << endl;
		}
	}
};

#endif // SAFFIX_ARRAY_HPP
