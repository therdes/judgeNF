#include "normalFormula.h"

int main(void)
{
	std::ifstream infile("data.txt");
	if (!infile)
		exit(-1);

	normalFormula nf(infile);

	auto ret2 = nf.is2NF();

	auto ret3 = nf.is3NF();

	return 0;
}