#include "orthogonal_list.h"

#include <iostream>

int main(void)
{
	orthogonal_list<std::string> graph;

	graph.add_edge("from", "to");

	auto ret = graph.adj_list("from");

	return 0;
}