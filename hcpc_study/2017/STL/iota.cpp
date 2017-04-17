#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
using namespace std;

template< typename T >
void dump(const T& obj) {
	for (int t : obj) cout << " " << t;
	cout << endl;
}

int main() {
	/***
		コンテナに要素数長の昇順列を格納する。
		第3引数に昇順列の最初の値を指定する。
	***/
	vector< int > vec(10);
	iota(vec.begin(), vec.end(), 0);
	dump(vec);
	
	list< int > lst(10);
	iota(lst.begin(), lst.end(), 5);
	dump(lst);
	
	string str(26, '#');
	iota(str.begin(), str.end(), 'a');
	cout << str << endl;
}
