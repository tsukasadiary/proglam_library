#include <bits/stdc++.h>
using namespace std;

#include "Treap.hpp"

int main() {
	Treap< int > treap;
	
	for (int i = 0; i < 10; ++i) treap.insert(i, i);
	
	treap.dump(cout);
	for (int i = 0; i < 10; ++i) cout << treap.find(i)->val << " ";
	cout << endl;
	
	while (1) {
		int x, l, r, v;
		cin >> x >> l >> r >> v;
		if (x == 0) treap.reverse(l, r + 1);
		if (x == 1) treap.rangeAdd(l, r + 1, v);
		treap.dump(cout);
		for (int i = 0; i < 10; ++i) cout << treap.find(i)->val << " ";
		cout << endl;
	}
}