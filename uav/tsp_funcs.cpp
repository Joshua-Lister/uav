#include "Circuit.h"
#include "genetic_algorithm.h"
#include "tsp_funcs.h"

//tsp_funcs::tsp_funcs();
//tsp_funcs::~tsp_funcs();
//extern vector<drone*> drones_v (number_of_drones);
//clustering obj1;
//clustering* obj1;
std::vector<address_metadata> test_route = set_dummy_route(5);
double fitness(Circuit& circ1)
{
	size_t rt_length = circ1.route.size();
	double f = 0;
	for (int i = 1; i < rt_length; i++)
		f += std::sqrt(util::length(circ1.route[i], circ1.route[i - 1]));
	return  1.0 / f;
}
std::vector<address_metadata> set_dummy_route(int rt_length)
{
	std::vector<address_metadata> obj(rt_length);
	for (int i = 0; i < rt_length; i++)
	{
		obj[i].x_coord = 1 + rand() % 100;
		obj[i].y_coord = 1 + rand() % 100;
		obj[i].num = i;
	}
	return obj;
}
double test_fitness(Circuit& circ)
{
	int rt_length = circ.route.size();
	double f = 0;
	for (int i = 1; i < rt_length - 1; i++)
		if (circ.route[i].num == test_route[i].num)
		{
			f++;
		}
	return f;
}

void initialise_circuit_v(std::vector<Circuit>& gen1, std::vector<Circuit>& gen2, std::vector<Circuit>& temp_gen, 
	std::vector<address_metadata>& obj1, int gen_size)
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