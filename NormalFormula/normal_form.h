#ifndef NORMAL_FORM_H
#define NORMAL_FORM_H

#include "schema_graph.h"
#include <tuple>
#include <memory>

class normal_form
{
public:
	normal_form() = default;
	normal_form(std::ifstream&);

	~normal_form() = default;

	bool is2NF();
	bool is3NF();
	bool isBCNF() const;

	void decompositeTo2NF();
	void decompositeTo3NF();
	void decompositeToBCNF();

private:
	using decomposite_action = std::tuple < int, std::string, std::string > ;

	const int DELETE = 1;

	std::shared_ptr<schema_graph> schema;

	std::vector<decomposite_action> to2NF;

	bool analize2NF(bool);

	void add_if_not_exist(const std::string&);
	void insert_in_right_place(const std::string&, const std::string&);
	bool find_transitive_dependencies(const std::string&) const;
};

#endif /* NORMAL_FORM_H */