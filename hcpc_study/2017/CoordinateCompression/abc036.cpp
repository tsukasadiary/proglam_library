#include <bits/stdc++.h>
using namespace std;

#define for_(i,a,b) for(int i=(a);i<(b);++i)
#define allof(a) (a).begin(),(a).end()

int main() {
	int N;
	cin >> N;
	
	vector< int > a(N);
	for_(i,0,N) cin >> a[i];
	
	vector< int > a_sort = a;
	sort(allof(a_sort));
	a_sort.erase(unique(allof(a_sort)), a_sort.end());
	
	for_(i,0,N) cout << (lower_bound(allof(a_sort), a[i]) - a_sort.begin()) << endl;
}
