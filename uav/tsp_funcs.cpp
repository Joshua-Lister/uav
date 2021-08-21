#include "Circuit.h"
#include "genetic_algorithm.h"
#include "tsp_funcs.h"

//tsp_funcs::tsp_funcs();
//tsp_funcs::~tsp_funcs();
//extern vector<drone*> drones_v (number_of_drones);
//clustering obj1;
//clustering* obj1;
clustering test_route = set_dummy_route(5);
double fitness(Circuit& circ1)
{
	size_t rt_length = circ1.route.size();
	double f = 0;
	for (int i = 1; i < rt_length; i++)
		f += std::sqrt(utility::length(circ1.route[i], circ1.route[i - 1]));
	return  1.0 / f;
}
clustering set_dummy_route(int rt_length)
{
	clustering c1(rt_length);
	for (int i = 0; i < rt_length; i++)
	{
		c1.centroids[i].x_coord = 1 + rand() % 100;
		c1.centroids[i].y_coord = 1 + rand() % 100;
		c1.centroids[i].num = i;
	}
	return c1;
}
double test_fitness(Circuit& circ)
{
	int rt_length = circ.route.size();
	double f = 0;
	for (int i = 1; i < rt_length - 1; i++)
		if (circ.route[i].num == test_route.centroids[i].num)
		{
			f++;
		}
	return f;
}

void initialise_circuit_v(vector<Circuit>& gen1, vector<Circuit>& gen2, vector<Circuit>& temp_gen, vector<address_metadata>& obj1, int gen_size)
{
	for (int i = 0; i < gen_size + 1; i++) 
	{
		gen1[i] = Circuit(obj1, false);
		gen2[i] = Circuit(obj1, true);
	}
	for (int i = 0; i < 2; i++)
		temp_gen[i] = Circuit(obj1, true);
}

bool check_truck_route_validity(Circuit& obj1) 
{
	int rt_size = obj1.route.size();
	for (int ic1 = 0; ic1 < rt_size; ic1++)
	{
		for (int ic2 = ic1 + 1; ic2 < rt_size; ic2++)
			if (obj1.route[ic1].num == obj1.route[ic2].num)
			{
				return false;
			}
	}
	return true;
}
bool check_validity_dummy(Circuit& obj1)
{
	return true;
}