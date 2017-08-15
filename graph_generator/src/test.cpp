#include "GraphGenerator.hpp"

int main() {
	GraphGenerator gg;
	GraphData graph = gg.randomGraph(10, 20);
	graph.shuffleID();
	graph.shuffleEdge();
	
	std::cout << graph.n << " " << graph.m << std::endl;
	for (int i=0; i<graph.m; ++i) std::cout << graph[i].u << " " << graph[i].v << std::endl;
}
