#ifndef NORMALFORMULA_H
#define NORMALFORMULA_H

#include <fstream>
#include <map>
#include <string>
#include <list>
#include <utility>
#include <memory>
#include <functional>
#include <vector>
#include <tuple>

class normalFormula
{
public:
	normalFormula() = default;
	normalFormula(std::ifstream&);

	~normalFormula() = default;

	bool is2NF();
	bool is3NF();
	bool isBCNF() const;

	void decompositeTo2NF();
	void decompositeTo3NF();
	void decompositeToBCNF();

private:
	using attrList_type = std::list < std::string > ;
	using schema_type = std::map < std::string, std::shared_ptr<attrList_type> > ;
	using decomposite_action = std::tuple < int, std::string, std::string > ;

	const int DELETE = 1;

	schema_type schema;

	std::vector<decomposite_action> to2NF;

	bool analize2NF(bool);

	void add_if_not_exist(const std::string&);
	void insert_in_right_place(const std::string&, const std::string&);
	bool find_transitive_dependencies(const std::string&) const;
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