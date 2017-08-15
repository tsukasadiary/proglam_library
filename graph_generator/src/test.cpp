#include "GraphGenerator.hpp"

int main() {
	GraphGenerator gg;
	GraphData graph = gg.randomGraph(10, 20);
	graph.shuffleID();
	graph.shuffleEdge();
	graph.dump(std::cerr);
}
