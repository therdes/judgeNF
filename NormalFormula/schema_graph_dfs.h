#ifndef SCHEMA_GRAPH_DFS_H
#define SCHEMA_GRAPH_DFS_H

#include "schema_graph.h"
#include <vector>
#include <set>

class schema_graph_dfs
{
public:
	using output_iterator = std::vector < std::vector<std::string> >::iterator;

public:
	schema_graph_dfs(const schema_graph&, output_iterator iter);

private:
	output_iterator& out_iter;

	std::vector<std::string> each_relational_table;

	std::set<std::string> marked;

	void dfs(const schema_graph&, const std::string&);

	bool is_marked(const std::string&);

	void add_this_table_to_output();
};

#endif