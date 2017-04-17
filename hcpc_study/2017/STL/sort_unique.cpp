#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

template< typename T  >
void dump(const T& obj) {
	for (int t : obj) cout << " " << t;
	cout << endl;
}

int main() {
	vector< int > vec = {1, 1, 4, 5, 1, 4};
	dump(vec);
	
	// ソートするには algorithm ヘッダーにある sort 関数に、ソートする範囲を iterator で渡すだけでよい。
	sort(vec.begin(), vec.end());
	dump(vec);
	
	/***
		unique はコンテナ内で同じ値が連続する箇所を見つけると、そのうち1つの値だけ残す。
		ただし、元のコンテナの長さを n 、unique 操作で【直感的に】に得られるコンテナの長さを m とすると、
		unique の結果は [unique されたコンテナ] + [元のコンテナの後ろ n-m 個分] なので注意が必要。
	***/
	list< int > uni = {2, 2, 3, 3, 3, 4, 4, 5, 3, 3, 2};
	auto it = unique(uni.begin(), uni.end());
	dump(uni);
	
	/***
		unique の元のコンテナの後ろ n-m 個分のうち最初の要素にあたる iterator である。
		よって、その iterator 以降を削除すれば、 unique 操作で【直感的に】得られるコンテナになる。
	***/
	uni.erase(it, uni.end());
	dump(uni);
	
	/***
		上記を応用すると、 コンテナの【完全な】 unique 操作は以下のように書ける。
		※ erase メソッドは指定された範囲の要素を削除する。
	***/ 
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	dump(vec);
}
