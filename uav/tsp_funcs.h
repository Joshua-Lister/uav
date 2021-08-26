#pragma once
#include "Circuit.h"
#include "genetic_algorithm.h"
extern std::vector<address_metadata> test_route;
double fitness(Circuit& circ1);
void initialise_circuit_v(std::vector<Circuit>& gen1, std::vector<Circuit>& gen2, std::vector<Circuit>& temp_gen, 
	std::vector<address_metadata>& obj1, int gen_size);
bool check_truck_route_validity(Circuit& obj1);
std::vector<address_metadata> set_dummy_route(int rt_length);
double test_fitness(Circuit& circ);
bool check_validity_dummy(Circuit& obj1);