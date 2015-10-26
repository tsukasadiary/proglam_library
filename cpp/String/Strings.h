#ifndef STRINGS_H
#define STRINGS_H

#ifndef TSUKASA_DIARY_S_TEMPLATE
#include "template.h"
#endif

// KMP
class KMP {
private:
	vector<int> fail;
	
public:
	KMP() {}
	
	int match(string _t, string _p) {
		int _n = size_of(_t), _m = size_of(_p);
		
		fail.assign(_m + 1, 0);
		int j = fail[0] = -1;
		
		for_(i,1,_m + 1) {
			while (j >= 0 && _p[j] != _p[i - 1]) j = fail[j];
			fail[i] = ++j;
		}
		
		int count = 0;
		for (int i = 0, k = 0; i < _n; ++i) {
			while (k >= 0 && _p[k] != _t[i]) k = fail[k];
			if (++k >= _m) {
				++count;
				k = fail[k];
			}
		}
		
		return count;
	}	
};

// Trie
class Alphabet {
public:
	static const int N = 4;
	
	inline int toInt(char c) {
		if (c == 'A') return 0;
		if (c == 'C') return 1;
		if (c == 'G') return 2;
		if (c == 'T') return 3;
		return -1;
	}
};

class Trie {
private:
	struct Node {
		vector< int > link;
		bool end;
		Node(int n) : link(n, -1),  end(false) {}
	};
	
	Alphabet& alph;
	vector< Node > node;
	
public:
	Trie(Alphabet& alph_) : alph(alph_) {
		node.push_back(Node(alph.N));
	}
	
	void insert(string& str) {
		insert(str, 0, 0);
	}
	
	void insert(string& str, int i, int vi) {
		if (i == size_of(str)) {
			node[vi].end = true;
			return;
		}
		
		int ci = alph.toInt(str[i]);
		
		if (node[vi].link[ci] != -1) {
			insert(str, i + 1, node[vi].link[ci]);
		} else {
			node.push_back(Node(alph.N));
			node[vi].link[ci] = size_of(node) - 1;
			insert(str, i + 1, node[vi].link[ci]);
		}
	}
	
	bool find(string& str) {
		return find(str, 0, 0);
	}
	
	bool find(string& str, int i, int vi) {
		if (i == size_of(str)) return node[vi].end;
		
		int ci = alph.toInt(str[i]);
		
		if (node[vi].link[ci] != -1) return find(str, i + 1, node[vi].link[ci]);
		return false;
	}
};

#endif // STRINGS_H