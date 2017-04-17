#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector< int > vec = {2, 5, 2, 5, 2};
	string str = "nicomaki$nozoeri$rinpana$kotohono$honoumi$";
	
	/***
		min_element ・ max_element 関数は、
		それぞれコンテナ中の指定されて範囲内で、
		最小・最大値に対応する最小のインデックスに当たる iterator を返す。
	***/
	cout << *min_element(vec.begin(), vec.end()) << endl;
	cout << *max_element(vec.begin(), vec.end()) << endl;
	
	cout << *min_element(str.begin(), str.end()) << endl;
	cout << *max_element(str.begin(), str.end()) << endl;
}
