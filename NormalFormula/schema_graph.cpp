#include "schema_graph.h"

using std::ifstream;
using std::string;
using std::make_shared;

schema_graph::schema_graph(ifstream& is)
{
	string line;
	while (is >> line)
		add_edge(line);
}

void schema_graph::add_edge(const string& line)
{
	auto index = line.find_first_of("->");
	string K = line.substr(0, index);
	string U = line.substr(index + 2);

	string::size_type i;
	while ((i = U.find_first_of(',')) != string::npos)
	{
		string attr = U.substr(0, i);
		add_if_not_exist(attr);
		insert_in_right_place(K, attr);
		U = U.substr(i + 1);
	}
	add_if_not_exist(U);
	insert_in_right_place(K, U);
}

schema_graph::adj_list_iter_pair schema_graph::adj(const string& attr)
{
	auto begin_iter = adj_list[attr]->begin();
	auto end_iter = adj_list[attr]->end();

	return adj_list_iter_pair(begin_iter, end_iter);
}

inline
void schema_graph::add_if_not_exist(const string& attr)
{
	if (adj_list.find(attr) == adj_list.end())
		adj_list[attr] = make_shared<attr_list_type>();
}

inline
void schema_graph::insert_in_right_place(const string& K, const string& U)
{
	if (K.find(',') != string::npos)
		adj_list[U]->insert(std::find_if(adj_list[U]->begin(), adj_list[U]->end(), more_than_one_attr()), K);
	else
		adj_list[U]->push_front(K);
}

inline
schema_graph::iterator schema_graph::begin()
{
	return adj_list.begin();
}
inline
schema_graph::const_iterator schema_graph::begin() const
{
	return adj_list.begin();
}

inline
schema_graph::iterator schema_graph::end()
{
	return adj_list.end();
}
inline
schema_graph::const_iterator schema_graph::end() const
{
	return adj_list.end();
}

inline
bool schema_graph::empty() const
{
	return adj_list.empty();
}

inline
schema_graph::size_type schema_graph::size() const
{
	return adj_list.size();
}

inline
schema_graph::mapped_type& schema_graph::operator[](const schema_graph::key_type& key)
{
	return adj_list[key];
}
inline
schema_graph::mapped_type& schema_graph::operator[](schema_graph::key_type&& key)
{
	return adj_list[key];
}

inline
schema_graph::iterator schema_graph::find(const schema_graph::key_type& key)
{
	return adj_list.find(key);
}
inline
schema_graph::const_iterator schema_graph::find(const schema_graph::key_type& key) const
{
	return adj_list.find(key);
}