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
	using value_type = adj_list_type::value_type;
	
	using key_compare = adj_list_type::key_compare;
	using value_compare = adj_list_type::value_compare;

	using const_iterator = adj_list_type::const_iterator;
	using iterator = adj_list_type::iterator;

	using size_type = adj_list_type::size_type;

public:
	schema_graph() = default;
	schema_graph(std::ifstream&);

	void add_edge(const std::string&);
	adj_list_iter_pair adj(const std::string&);

	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

	bool empty() const;
	size_type size() const;

	mapped_type& operator[](const key_type&);
	mapped_type& operator[](key_type&&);

	iterator find(const key_type&);
	const_iterator find(const key_type&) const;

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