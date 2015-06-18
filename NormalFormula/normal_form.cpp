#include "normal_form.h"

#include <algorithm>
#include <set>
#include <queue>
#include <iterator>

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

normal_form::normal_form(ifstream& is)
{
	schema = make_shared<schema_graph>(is);
}

bool normal_form::is2NF()
{
	return analize2NF(to2NF.empty());
}

bool normal_form::analize2NF(bool add_action)
{
	bool ret = true;
	for (auto each_func : *schema)
	{
		auto splice = find_if(each_func.second->begin(), each_func.second->end(), more_than_one_attr());
		for (auto i = each_func.second->begin(); i != splice; i++)
			for (auto j = splice; j != each_func.second->end(); j++)
				if (j->find(*i) != string::npos)
				{
					ret = false;
					if (add_action)
						to2NF.push_back(decomposite_action(DELETE, each_func.first, *j));
				}
	}
	return ret;
}

bool normal_form::is3NF()
{
	if (!is2NF())
		return false;

	for (auto each_func : *schema)
		if (find_transitive_dependencies(each_func.first))
			return false;
	return true;
}

void normal_form::decompositeTo2NF()
{
	for (auto item : to2NF)
	{
		if (get<0>(item) == DELETE)
		{
			auto attr_list = schema->operator[](get<1>(item));
			attr_list->erase(find(attr_list->begin(), attr_list->end(), get<2>(item)));
		}
	}
	to2NF.clear();
}

bool normal_form::find_transitive_dependencies(const string& start) const
{
	set<string> marked;

	queue<string> q;
	q.push(start);
	while (!q.empty())
	{
		auto curr = q.front();
		if (marked.find(curr) != marked.end())
			return true;
		else
			marked.insert(curr);
		q.pop();

		auto pos = schema->find(curr);
		if (pos != schema->end())
		{
			auto attr_list = *pos->second;
			for (auto iter : attr_list)
				q.push(iter);
		}
	}
	return false;
}