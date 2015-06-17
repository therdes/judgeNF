#ifndef NORMALFORMULA_H
#define NORMALFORMULA_H

#include <fstream>
#include <map>
#include <string>
#include <list>
#include <utility>
#include <memory>
#include <functional>

class normalFormula
{
public:
	normalFormula() = default;
	normalFormula(std::ifstream&);

	~normalFormula() = default;

	bool is2NF() const;
	bool is3NF() const;
	bool isBCNF() const;

	void decompositeTo2NF();
	void decompositeTo3NF();
	void decompositeToBCNF();

private:
	using attrList_type = std::list < std::string > ;
	using schema_type = std::map < std::string, std::shared_ptr<attrList_type> > ;

	schema_type schema;

	void add_if_not_exist(const std::string&);
	void insert_in_right_place(const std::string&, const std::string&);
	bool find_transitive_dependencies(const std::string&) const;
};

struct more_than_one_attr : public std::unary_function<std::string, bool>
{
	bool operator()(const std::string& str) const
	{
		if (str.find(',') != std::string::npos)
			return true;
		return false;
	}
};

#endif