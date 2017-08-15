### GraphGenerator

競技プログラミングにおける、グラフのデータセット作成に役立てたい気持ち

- 使用例 (src/test.cpp)
	
	```c
	#include "GraphGenerator.hpp"
	
	int main() {
		GraphGenerator gg;
		GraphData graph = gg.randomGraph(10, 20);
		graph.shuffleID();
		graph.shuffleEdge();
		graph.dump(std::cerr);
	}
	```

- 出力例
	```
	10 20
	6 0
	8 4
	9 8
	4 3
	2 1
	0 3
	8 7
	0 2
	2 6
	9 3
	3 2
	5 0
	6 8
	9 1
	8 0
 	3 5
	7 0
	7 2
	6 9
	1 8
	```
