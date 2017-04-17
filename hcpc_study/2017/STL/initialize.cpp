#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <typeinfo>
#include <algorithm>
using namespace std;

template< typename T  >
void dump(const T& obj) {
	for (int t : obj) cout << " " << t;
	cout << endl;
}

int main() {
	vector< int > vec_int_1 = {8, 1, 0};
	list< int > list_int_1 = {9, 3, 1};
	set< int > set_int_1 = {1, 1, 4, 5, 1, 4};
	
	/***
	 一方のコンテナの各値を順に他方のコンテナに入れることで初期化できる。
	 iterator で範囲を指定する。
	***/
	vector< int > vec_int_2(list_int_1.begin(), list_int_1.end()); // vector <- list
	dump(vec_int_2);
	
	list< int > list_int_2(set_int_1.begin(), set_int_1.end()); // list <- set
	dump(list_int_2);
	
	set< int > set_int_2(vec_int_1.begin(), vec_int_1.end()); // set <- vector
	dump(set_int_2);
}
