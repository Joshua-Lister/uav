#include "Circuit.h"
#include "genetic_algorithm.h"

template <class C>
double genetic_algorithm<C>::fitness(C& circ1)
{
	size_t rt_length = circ1.route.size();
	double f = 0;
	for (int i = 1; i < rt_length; i++)
		f += utility::length(circ1.route[i], circ1.route[i - 1]);
	return  1.0 / f;
}
template <class C>
void genetic_algorithm<C>::initialise_circuit_v(vector<C>& gen1, vector<C>& gen2, vector<C>& temp_gen)
{
	for (int i = 0; i < lista.generation_size + 1; i++) {
		gen1[i] = C(obj1.centroids, false);
		gen2[i] = C(obj1.centroids, true);
	}
	for (int i = 0; i < 2; i++)
		temp_gen[i] = C(obj1.centroids, true);
}