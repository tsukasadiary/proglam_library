#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector< int > vec = {2, 5, 2, 5, 2};
	string str = "nicomaki$nozoeri$rinpana$kotohono$honoumi$";
	
	/***
		find 関数はコンテナ中の指定された範囲内で要素検索を行い、
		該当する最小のインデックスにあたる iterator を返す。
		見つからない時は末尾を返す。
	***/
	cout << find(vec.begin(), vec.end(), 5) - vec.begin() << endl;
	cout << find(vec.begin(), vec.end(), 114514) - vec.begin() << endl;
	
	cout << find(str.begin(), str.end(), 'o') - str.begin() << endl;
	cout << find(str.begin(), str.end(), '#') - str.begin() << endl;
	
	/***
		find 関数で string を突っ込むと文字検索しかできない。
		string 固有の find メソッドがあり、こちらは文字列でも検索ができる。（範囲指定はちょっと融通が効かなくなる）
		見つからない時は [var_name].npos という値を返すので注意すること。
	***/
	cout << str.find("hono") << endl;
	cout << str.find("pana", 10) << endl; // 11文字目以降が検索範囲
	cout << str.find("ruby") << " " << str.npos << endl;
}
