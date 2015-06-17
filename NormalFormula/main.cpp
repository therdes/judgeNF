#include "normal_form.h"

int main(void)
{
	std::ifstream infile("data.txt");
	if (!infile)
		exit(-1);

	normal_form nf(infile);

	auto ret2 = nf.is2NF();

	auto ret3 = nf.is3NF();

	nf.decompositeTo2NF();
	ret2 = nf.is2NF();
	ret3 = nf.is3NF();

	return 0;
}