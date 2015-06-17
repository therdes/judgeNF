#include "normalFormula.h"

#include <algorithm>
#include <set>
#include <queue>

normalFormula::normalFormula(std::ifstream& is)
{
	std::string line;
	while (is >> line)
	{
		auto index = line.find_first_of("->");
		std::string K = line.substr(0, index);
		std::string U = line.substr(index + 2);

		std::string::size_type i;
		while ((i = U.find_first_of(',')) != std::string::npos)
		{
			std::string attr = U.substr(0, i);
			add_if_not_exist(attr);
			insert_in_right_place(K, attr);
			U = U.substr(i + 1);
		}
		add_if_not_exist(U);
		insert_in_right_place(K, U);
	}
}

bool normalFormula::is2NF()
{
	return analize2NF(to2NF.empty());
}

bool normalFormula::analize2NF(bool add_action)
{
	bool ret = true;
	for (auto each_func : schema)
	{
		auto splice = std::find_if(each_func.second->begin(), each_func.second->end(), more_than_one_attr());
		for (auto i = each_func.second->begin(); i != splice; i++)
			for (auto j = splice; j != each_func.second->end(); j++)
				if (j->find(*i) != std::string::npos)
				{
					ret = false;
					if (add_action)
						to2NF.push_back(decomposite_action(DELETE, each_func.first, *j));
				}
	}
	return ret;
}

bool normalFormula::is3NF()
{
	if (!is2NF())
		return false;

	for (auto each_func : schema)
		if (find_transitive_dependencies(each_func.first))
			return false;
	return true;
}

void normalFormula::decompositeTo2NF()
{
	for (auto item : to2NF)
	{
		if (std::get<0>(item) == DELETE)
		{
			auto& attr_list = *schema[std::get<1>(item)];
			attr_list.erase(std::find(attr_list.begin(), attr_list.end(), std::get<2>(item)));
		}
	}
	to2NF.clear();
}

inline
void normalFormula::add_if_not_exist(const std::string& attr)
{
	if (schema.find(attr) == schema.end())
		schema[attr] = std::make_shared<attrList_type>();
}

inline
void normalFormula::insert_in_right_place(const std::string& K, const std::string& U)
{
	if (K.find(',') != std::string::npos)
		schema[U]->insert(std::find_if(schema[U]->begin(), schema[U]->end(), more_than_one_attr()), K);
	else
		schema[U]->push_front(K);
}

bool normalFormula::find_transitive_dependencies(const std::string& start) const
{
	std::set<std::string> marked;

	std::queue<std::string> q;
	q.push(start);
	while (!q.empty())
	{
		auto curr = q.front();
		if (marked.find(curr) != marked.end())
			return true;
		else
			marked.insert(curr);
		q.pop();

		auto pos = schema.find(curr);
		if (pos != schema.end())
		{
			auto attr_list = *pos->second;
			for (auto iter : attr_list)
				q.push(iter);
		}
	}
	return false;
}