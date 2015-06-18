#ifndef SCHEMA_GRAPH_H
#define SCHEMA_GRAPH_H

#include <map>
#include <algorithm>
#include <memory>
#include <utility>
#include <fstream>
#include <list>
#include <string>
#include <functional>

class schema_graph
{
private:
	using attr_list_type = std::list < std::string >;
	using adj_list_type = std::map < std::string, std::shared_ptr<std::list<std::string>> >;

public:
	using adj_list_iter_pair = std::pair < std::list<std::string>::iterator, std::list<std::string>::iterator > ;
	using key_type = adj_list_type::key_type;
	using mapped_type = adj_list_type::mapped_type;
	using const_iterator = adj_list_type::const_iterator;
	using iterator = adj_list_type::iterator;

public:
	schema_graph() = default;
	schema_graph(std::ifstream&);

	void add_edge(const std::string&);
	adj_list_iter_pair adj(const std::string&);

	mapped_type operator[](const key_type&);
	iterator find(const key_type&);

	iterator begin();
	const_iterator cbegin() const;

	iterator end();
	const_iterator cend() const;

private:
	adj_list_type adj_list;

	void add_if_not_exist(const std::string&);
	void insert_in_right_place(const std::string&, const std::string&);
};

struct more_than_one_attr : public std::unary_function < std::string, bool >
{
	bool operator()(const std::string& str) const
	{
		if (str.find(',') != std::string::npos)
			return true;
		return false;
	}
};

#endif