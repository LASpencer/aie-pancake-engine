#include "stdafx_test.h"
#include "catch.hpp"
#include "MapGraph.h"

TEST_CASE("Map Graph") {
	MapGraph graph;

	graph.addNode({ 200,600 });
	graph.addNode({ 400,600 });
	graph.addNode({ 400,450 });
	graph.addNode({ 400,300 });
	graph.addNode({ 300,150 });
	graph.addNode({ 200,300 });

	graph.addEdge(0, 1, 2);
	graph.addEdge(0, 5, 5);
	graph.addEdge(1, 2, 3);
	graph.addEdge(2, 0, 3);
	graph.addEdge(2, 3, 1);
	graph.addEdge(3, 4, 4);
	graph.addEdge(3, 5, 4);
	graph.addEdge(4, 0, 99);
	graph.addEdge(5, 4, 6);

	SECTION("Dijkstra's algorithm") {
		std::stack<glm::vec2> path = graph.dijkstraSearch(0, 4);
		//std::vector<glm::vec2> result = {,{  },{ 400,450 },{ 300,150 } };
		REQUIRE(path.top() == glm::vec2( 200, 600 ));
		path.pop();
		REQUIRE(path.top() == glm::vec2( 400,600 ));
		path.pop();
		REQUIRE(path.top() == glm::vec2( 400,450 ));
		path.pop();
		REQUIRE(path.top() == glm::vec2(400, 300));
		path.pop();
		REQUIRE(path.top() == glm::vec2( 300,150 ));
		path.pop();
		REQUIRE(path.empty());
	}
}