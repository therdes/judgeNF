#include "normal_form.h"

#include <iostream>
#include <fstream>
using std::ifstream;
using std::ios;

int main(void)
{
	ifstream infile("data.txt", ios::in);
	if (!infile)
		exit(-1);

	normal_form schema(infile);
	auto ret2 = schema.is2NF();
	auto ret3 = schema.is3NF();

	return 0;
}