#pragma once
extern vector<address_metadata> test_route;
double fitness(Circuit& circ1);
void initialise_circuit_v(vector<Circuit>& gen1, vector<Circuit>& gen2, vector<Circuit>& temp_gen, vector<address_metadata>& obj1, int gen_size);
bool check_truck_route_validity(Circuit& obj1);
vector<address_metadata> set_dummy_route(int rt_length);
double test_fitness(Circuit& circ);
bool check_validity_dummy(Circuit& obj1);