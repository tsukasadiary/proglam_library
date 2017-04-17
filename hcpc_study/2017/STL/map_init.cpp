#include <iostream>
#include <map>
using namespace std;

template< typename F, typename T >
void dump(const map< F, T >& m) {
	for (auto p : m) cout << p.first << " " << p.second << endl;
	cout << endl;
}

int main() {
	// map の各要素 <key, value> を {key, value} として書くことで初期化できる。
	map< char, int > map_ci = {{'1', 1}, {'a', 2}, {'p', 10}, {'c', 2}, {'#', 11}};
	dump(map_ci);
	
	// map には insert 機能もあり、この仕様も上記同様である。計算時間はもちろん O(log n) だぞい。
	map_ci.insert({'*', 5});
	dump(map_ci);
}
