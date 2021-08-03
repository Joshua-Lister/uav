#include "genetic_algorithm.h"

double genetic_algorithm::fitness(Circuit& circ1)
{
	double f = 0;
	for (int i = 1; i < rt_size; i++)
		f += utility::length(circ1.route[i], circ1.route[i - 1]);
	return  1.0 / f;
}