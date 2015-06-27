#include "normal_form.h"

#include <set>
#include <queue>
#include <iterator>
#include <map>
#include <functional>

using std::vector;
using std::ifstream;
using std::string;
using std::set;
using std::queue;
using std::ostream;
using std::map;
using std::set_intersection;
using std::shared_ptr;
using std::make_shared;
using std::inserter;
using std::get;
using std::find;
using std::unary_function;
using std::not1;

struct more_than_one_attr : public unary_function < std::string, bool >
{
	bool operator()(const std::string& str) const
	{
		if (str.find(',') != std::string::npos)
			return true;
		return false;
	}
};

normal_form::normal_form(ifstream& is)
{
	schema = make_shared<orthogonal_list<string>>(is);
}

bool normal_form::is2NF() const
{
	return analize2NF();
}

bool normal_form::analize2NF() const
{
	auto ret = true;
	for (auto vertex : schema->all_vertex())
	{
		auto vertex_list = schema->reverse_adj_list(vertex, not1(more_than_one_attr()));
		auto splice = std::find_if(vertex_list.begin(), vertex_list.end(), more_than_one_attr());
		for (auto one_attr = vertex_list.begin(); one_attr != splice; one_attr++)
		{
			for (auto more_attr = splice; more_attr != vertex_list.end(); more_attr++)
			{
				if (more_attr->find_first_of(*one_attr) != string::npos)
					ret = false;
			}
		}
	}

	return ret;
}

bool normal_form::is3NF() const
{
	if (!is2NF())
		return false;

	bool ret = true;
	for (auto vertex : schema->all_vertex())
		if (find_transitive_dependencies(vertex))
			ret = false;

	return ret;
}

bool normal_form::find_transitive_dependencies(const string& attr) const
{
	bool ret = false;
	set<string> attr_list;
	
	queue<string> attr_queue;
	attr_queue.push(attr);
	while (!attr_queue.empty())
	{
		auto attr = attr_queue.front();
		attr_queue.pop();

		if (attr_list.find(attr) != attr_list.end())
			ret = true;
		else
			attr_list.insert(attr);

		for (auto item : schema->adj_list(attr))
			attr_queue.push(item);
	}

	return ret;
}