#ifndef NORMAL_FORM_H
#define NORMAL_FORM_H

#include "orthogonal_list.h"
#include <tuple>
#include <memory>

class normal_form
{
public:
	normal_form() = default;
	normal_form(std::ifstream&);

	~normal_form() = default;

	bool is2NF() const;
	bool is3NF() const;
	bool isBCNF() const;

	void decompositeTo2NF();
	void decompositeTo3NF();
	void decompositeToBCNF();

private:
	using decomposite_action = std::tuple < int, std::string, std::string > ;

	const int DELETE = 1;

	std::shared_ptr<orthogonal_list<std::string>> schema;

	std::vector<decomposite_action> to2NF;

	bool analize2NF() const;
	bool find_transitive_dependencies(const std::string&) const;
};

#endif /* NORMAL_FORM_H */