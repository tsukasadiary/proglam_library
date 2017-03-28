#include <bits/stdc++.h>
using namespace std;

#define for_(i,a,b) for(int i=(a);i<(b);++i)
#define allof(a) (a).begin(),(a).end()

int w, h, n, lft[500], bot[500], rgt[500], top[500];
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

int compress(int* a, int* b, int mx) {
	vector< int > ext_c;
	ext_c.push_back(1); ext_c.push_back(mx);
	
	for_(i,0,n) {
		ext_c.push_back(a[i]);
		if (a[i] + 1 <= mx) ext_c.push_back(a[i] + 1);
		ext_c.push_back(b[i]);
		if (b[i] + 1 <= mx) ext_c.push_back(b[i] + 1);
	}
	
	sort(allof(ext_c));
	ext_c.erase(unique(allof(ext_c)), ext_c.end());
	
	for_(i,0,n) {
		a[i] = lower_bound(allof(ext_c), a[i]) - ext_c.begin();
		b[i] = lower_bound(allof(ext_c), b[i]) - ext_c.begin();
	}
	
	return ext_c.size();
}

int search() {
	int search_cnt = 0;
	
	struct State { int x, y; };
	enum Cell { NON = 0, WALL = 1, VISITED = 2, };
	
	vector< vector< Cell > > field(h, vector< Cell >(w, NON));
	for_(i,0,n) for_(y,bot[i],top[i]+1) for_(x,lft[i],rgt[i]+1) field[y][x] = WALL;
	
	for_(y,0,h) for_(x,0,w) {
		if (field[y][x] == NON) {
			queue< State > que;
			que.push(State{x, y});
			field[y][x] = VISITED;
			
			while (!que.empty()) {
				State s = que.front(); que.pop();
				for_(d,0,4) {
					int nx = s.x + dx[d], ny = s.y + dy[d];
					if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;
					if (field[ny][nx] != NON) continue;
					field[ny][nx] = VISITED;
					que.push(State{nx, ny});
				}
			}
			
			++search_cnt;
		}
	}
	
	return search_cnt;
}

void solve() {
	w = compress(lft, rgt, w);
	h = compress(bot, top, h);
	cout << search() << endl;;
}

int main() {
	cin >> w >> h >> n;
	for_(i,0,n) cin >> lft[i] >> bot[i] >> rgt[i] >> top[i];
	solve();
}
