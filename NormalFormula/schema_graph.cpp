#include "schema_graph.h"

using std::ifstream;
using std::string;
using std::binary_function;

schema_graph::schema_graph(ifstream& is)
{
	string line;
	while (is >> line)
		add_dependent_edge(line);
}

void schema_graph::add_dependent_edge(const string& line)
{
	auto index = line.find_first_of("->");
	string K = line.substr(0, index);
	string U = line.substr(index + 2);

	string::size_type i;
	while ((i = U.find_first_of(',')) != string::npos)
	{
		string attr = U.substr(0, i);
		edge_list.push_back(dependent_func(K, attr));
		U = U.substr(i + 1);
	}
	edge_list.push_back(dependent_func(K, U));

	add_trivial_dependency(K);
}

void schema_graph::add_trivial_dependency(const string& K)
{
	string K_dup(K);
	string::size_type i;
	while ((i = K_dup.find_first_of(',')) != string::npos)
	{
		string attr = K_dup.substr(0, i);
		edge_list.push_back(dependent_func(K, attr));
		K_dup = K_dup.substr(i + 1);
	}
	if (K != K_dup)
		edge_list.push_back(dependent_func(K, K_dup));
}

schema_graph::iterator schema_graph::begin()
{
	return edge_list.begin();
}
schema_graph::const_iterator schema_graph::begin() const
{
	return edge_list.begin();
}

schema_graph::iterator schema_graph::end()
{
	return edge_list.end();
}
schema_graph::const_iterator schema_graph::end() const
{
	return edge_list.end();
}

schema_graph::reference schema_graph::operator[](schema_graph::size_type n)
{
	return edge_list[n];
}
schema_graph::const_reference schema_graph::operator[](schema_graph::size_type n) const
{
	return edge_list[n];
}