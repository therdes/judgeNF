#include "schema_graph_dfs.h"
using std::vector;
using std::string;

schema_graph_dfs::schema_graph_dfs(const schema_graph& g, schema_graph_dfs::output_iterator iter)
	: out_iter(iter)
{
	each_relational_table.clear();

	for (auto item : g)
	{
		if (!is_marked(item.first))
			dfs(g, item.first);
		add_this_table_to_output();
	}
}

bool schema_graph_dfs::is_marked(const string& attr)
{
	return marked.find(attr) != marked.end();
}

void schema_graph_dfs::add_this_table_to_output()
{
	*out_iter++ = each_relational_table;
	each_relational_table.clear();
}

void schema_graph_dfs::dfs(const schema_graph& g, const string& attr)
{

}