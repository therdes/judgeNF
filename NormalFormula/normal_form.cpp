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
		auto vertex_list = schema->reverse_adj_list(vertex, more_than_one_attr());
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
