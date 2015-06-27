#ifndef ORTHOGONAL_LIST_H
#define ORTHOGONAL_LIST_H

#include <stdexcept>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

template<typename VertexType>
class list_node
{
public:
	list_node(const VertexType& out_val, const VertexType& in_val) :
		out_vertex_value(out_val), in_vertex_value(in_val), weight(1),
		next_out(nullptr), next_in(nullptr) {}
	list_node(const VertexType& out_val, const VertexType& in_val, double w) :
		out_vertex_value(out_val), in_vertex_value(in_val), weight(w),
		next_out(nullptr), next_in(nullptr) {}

	list_node*& next_out_vertex()
	{
		return next_out;
	}
	list_node* next_out_vertex() const
	{
		return next_out;
	}

	list_node*& next_in_vertex()
	{
		return next_in;
	}
	list_node* next_in_vertex() const
	{
		return next_in;
	}

	const VertexType out_vertex() const
	{
		return out_vertex_value;
	}
	const VertexType in_vertex() const
	{
		return in_vertex_value;
	}

	double& edge_weight()
	{
		return weight;
	}
	double edge_weight() const
	{
		return weight;
	}

	const VertexType other(const VertexType& v) const
	{
		if (v == out_vertex_value)
			return in_vertex_value;
		else if (v == in_vertex_value)
			return out_vertex_value;
		else
			throw new std::exception("unaccept argument");
	}

private:
	VertexType out_vertex_value;
	VertexType in_vertex_value;

	double weight;

	list_node* next_out;
	list_node* next_in;
};

template<typename VertexType>
class orthogonal_list
{
private:
	using edge_ptr_pair = std::pair < list_node<VertexType>*, list_node<VertexType>* > ;
	using vertex_list_type = std::map < VertexType, edge_ptr_pair > ;

public:
	orthogonal_list() = default;
	orthogonal_list(int v) : vertexes(v), edges(0) {}
	orthogonal_list(std::ifstream&);

	~orthogonal_list();

	void add_edge(const std::string&);
	void add_edge(const VertexType&, const VertexType&);

	const std::vector<VertexType> all_vertex();

	const std::vector<VertexType> adj_list(const VertexType&);
	template<typename Pred>
	const std::vector<VertexType> adj_list(const VertexType&, Pred);

	const std::vector<VertexType> reverse_adj_list(const VertexType&);
	template<typename Pred>
	const std::vector<VertexType> reverse_adj_list(const VertexType&, Pred);

private:
	vertex_list_type vertex_list;

	int vertexes = 0;
	int edges = 0;

	void push_front(const VertexType&, list_node<VertexType>*, bool);

	void clear_list(const list_node<VertexType>*);

	const std::vector<VertexType> adjacency_list(const VertexType&, bool);
	template<typename Pred>
	const std::vector<VertexType> adjacency_list(const VertexType&, bool, Pred);
};

template<typename VertexType>
orthogonal_list<VertexType>::orthogonal_list(std::ifstream& is)
{
	std::istream_iterator<std::string> is_iter(is), eos;
	while (is_iter != eos)
		add_edge(*is_iter++);
}

template<typename VertexType>
orthogonal_list<VertexType>::~orthogonal_list()
{
	for (auto item : vertex_list)
	{
		auto ptr = item.second.second;
		clear_list(ptr);
	}
}

template<typename VertexType>
void orthogonal_list<VertexType>::add_edge(const std::string& func_dependency)
{
	auto index = func_dependency.find_first_of("->");
	std::string K = func_dependency.substr(0, index);
	std::string U = func_dependency.substr(index + 2);

	std::string::size_type i;
	while ((i = U.find_first_of(',')) != std::string::npos)
	{
		std::string attr = U.substr(0, i);
		add_edge(K, attr);
		U = U.substr(i + 1);
	}
	add_edge(K, U);
}

template<typename VertexType>
void orthogonal_list<VertexType>::add_edge(const VertexType& from, const VertexType& to)
{
	auto node = new list_node<VertexType>(from, to);

	if (vertex_list.find(from) == vertex_list.end())
	{
		vertex_list[from] = edge_ptr_pair(nullptr, nullptr);
		vertexes += 1;
	}

	push_front(from, node, false);

	if (vertex_list.find(to) == vertex_list.end())
	{
		vertex_list[to] = edge_ptr_pair(nullptr, nullptr);
		vertexes += 1;
	}

	push_front(to, node, true);

	edges += 1;
}

template<typename VertexType>
void orthogonal_list<VertexType>::push_front(const VertexType& vertex_val,
	list_node<VertexType>* node, bool is_reverse)
{
	auto& operate_ptr = is_reverse ? vertex_list[vertex_val].first : vertex_list[vertex_val].second;
	auto& node_next_ptr = is_reverse ? node->next_in_vertex() : node->next_out_vertex();

	node_next_ptr = operate_ptr;
	operate_ptr = node;
}

template<typename VertexType>
void orthogonal_list<VertexType>::clear_list(const list_node<VertexType>* ptr)
{
	auto curr = ptr;
	while (curr != nullptr)
	{
		auto next = curr->next_out_vertex();
		delete curr;
		curr = next;
	}
}

template<typename VertexType>
const std::vector<VertexType>
orthogonal_list<VertexType>::all_vertex()
{
	std::vector<VertexType> ret;
	ret.reserve(vertexes);
	for (auto item : vertex_list)
		ret.push_back(item.first);
	return ret;
}

template<typename VertexType>
const std::vector<VertexType>
orthogonal_list<VertexType>::adjacency_list(const VertexType& val, bool is_reverse)
{
	auto result = vertex_list.find(val);
	if (result == vertex_list.end())
		return std::vector<VertexType>();

	auto curr = is_reverse ? result->second.first : result->second.second;
	std::vector<VertexType> ret;
	while (curr != nullptr)
	{
		auto next = is_reverse ? curr->next_in_vertex() : curr->next_out_vertex();
		ret.push_back(is_reverse ? curr->out_vertex() : curr->in_vertex());
		curr = next;
	}

	return ret;
}

template<typename VertexType>
template<typename Pred>
const std::vector<VertexType>
orthogonal_list<VertexType>::adjacency_list(const VertexType& val, bool is_reverse, Pred pred)
{
	auto ret = adjacency_list(val, is_reverse);
	std::partition(ret.begin(), ret.end(), pred);
	return ret;
}

template<typename VertexType>
const std::vector<VertexType>
orthogonal_list<VertexType>::adj_list(const VertexType& val)
{
	return adjacency_list(val, false);
}

template<typename VertexType>
template<typename Pred>
const std::vector<VertexType>
orthogonal_list<VertexType>::adj_list(const VertexType& val, Pred pred)
{
	return adjacency_list(val, false, pred);
}

template<typename VertexType>
const std::vector<VertexType>
orthogonal_list<VertexType>::reverse_adj_list(const VertexType& val)
{
	return adjacency_list(val, true);
}

template<typename VertexType>
template<typename Pred>
const std::vector<VertexType>
orthogonal_list<VertexType>::reverse_adj_list(const VertexType& val, Pred pred)
{
	return adjacency_list(val, true, pred);
}

#endif