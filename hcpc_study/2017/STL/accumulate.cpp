#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector< int > vec_int = {2, 5, 2, 5, 2};
	vector< string > vec_str = {"nicomaki$", "nozoeri$", "rinpana$", "kotohono$", "honoumi$"};
	
	/***
		accumulate 関数はコンテナ中の指定された範囲内の要素に + 演算子を適用した結果を返す。
		ちなみに、3つ目の引数は + 演算する前の初期値として設定される。
	***/
	cout << accumulate(vec_int.begin(), vec_int.end(), int()) << endl;
	cout << accumulate(vec_str.begin(), vec_str.end(), string()) << endl;
	
	cout << accumulate(vec_int.begin(), vec_int.end(), int(10)) << endl;
	cout << accumulate(vec_str.begin(), vec_str.end(), string("ruby$")) << endl;
}
