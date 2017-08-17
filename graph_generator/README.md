### GraphGenerator

競技プログラミングにおける、グラフのデータセット作成に役立てたい気持ち

### ToDo
- 作れるグラフを増やす
- 重み付けに対応
- 有向グラフに対応
- Dinic殺すマンに対応
- 根付き木表現に対応 (各頂点の親を指定するフォーマット)

### 仕様

- 中身
```c
// 0-index で "連結で単純な" グラフを作る
class GraphGenerator {
	XorShift rnd;
	
public:
	GraphGenerator() {}

	GraphData pathGraph(int n);           // n 頂点のパスグラフ
	GraphData cycleGraph(int n);          // n 頂点のサイクルグラフ
	GraphData gridGraph(int X, int Y);    // X * Y 頂点のグリッドグラフ
	GraphData completeGraph(int n);       // n 頂点の完全グラフ
	GraphData kBranchTree(int k, int h);  // 各頂点からの分岐数 k、 高さ h の木
	GraphData bunchGraph(int med);        // 頂点数 med+2、頂点 0 と {1,...,med} の間、および {1,..,med} と頂点 med+1 の間に辺がある	
	GraphData randomGraph(int n, int m);  // n 頂点 m 辺からなるランダムグラフ
};
```

- 使用例 (src/test.cpp)
	
```c
#include "GraphGenerator.hpp"
int main() {
	GraphGenerator gg;
	GraphData graph = gg.randomGraph(10, 20);
	graph.shuffleID();
	graph.shuffleEdge();

	std::cout << graph.n << " " << graph.m << std::endl;
	for (int i=0; i<graph.m; ++i) std::cout << graph[i].u << " " << graph[i].v << std::endl;
	// graph.dump(std::cout); でも同じ
}
```

- 出力例
```
10 20
5 3
1 5
7 5
0 3
0 8
6 1
9 1
3 2
7 0
1 7
4 3
2 5
5 0
6 8
9 5
1 4
9 6
8 1
6 5
4 9
```
