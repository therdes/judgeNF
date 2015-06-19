#ifndef SCHEMA_GRAPH_H
#define SCHEMA_GRAPH_H

#include <utility>
#include <fstream>
#include <string>
#include <vector>

//class schema_graph
//{
//private:
//	using attr_list_type = std::list < std::string >;
//	using map_adapter = std::map < std::string, std::shared_ptr<std::list<std::string>> >;
//
//public:
//	using adj_list_iter_pair = std::pair < std::list<std::string>::iterator, std::list<std::string>::iterator > ;
//
//	using key_type = map_adapter::key_type;
//	using mapped_type = map_adapter::mapped_type;
//	using value_type = map_adapter::value_type;
//	
//	using iterator = map_adapter::iterator;
//	using const_iterator = map_adapter::const_iterator;
//
//	using size_type = map_adapter::size_type;
//
//public:
//	schema_graph() = default;
//	schema_graph(std::ifstream&);
//
//	void add_edge(const std::string&);
//	adj_list_iter_pair adj(const std::string&);
//
//	iterator begin();
//	const_iterator begin() const;
//
//	iterator end();
//	const_iterator end() const;
//
//	bool empty() const;
//	size_type size() const;
//
//	mapped_type& operator[](const key_type&);
//	mapped_type& operator[](key_type&&);
//
//	iterator find(const key_type&);
//	const_iterator find(const key_type&) const;
//
//private:
//	map_adapter adj_list;
//
//	void add_if_not_exist(const std::string&);
//	void insert_in_right_place(const std::string&, const std::string&);
//};
//
//struct more_than_one_attr : public std::unary_function < std::string, bool >
//{
//	bool operator()(const std::string& str) const
//	{
//		if (str.find(',') != std::string::npos)
//			return true;
//		return false;
//	}
//};

struct add_in_list;

class schema_graph
{
private:
	using dependent_func = std::pair < std::string, std::string > ;
	using graph_type = std::vector < dependent_func > ;

public:
	using value_type = graph_type::value_type;

	using iterator = graph_type::iterator;
	using const_iterator = graph_type::const_iterator;

	using reference = graph_type::reference;
	using const_reference = graph_type::const_reference;

	using size_type = graph_type::size_type;

	schema_graph() = default;
	schema_graph(std::ifstream&);

	void add_dependent_edge(const std::string&);

	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

	reference operator[](size_type);
	const_reference operator[](size_type) const;

private:
	graph_type edge_list;

	void add_trivial_dependency(const std::string&);
};

#endif