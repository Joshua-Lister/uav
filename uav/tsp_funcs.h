#pragma once

double fitness(Circuit& circ1);
void initialise_circuit_v(vector<Circuit>& gen1, vector<Circuit>& gen2, vector<Circuit>& temp_gen, vector<address_metadata>& obj1, int gen_size);
bool check_truck_route_validity(vector<address_metadata>& obj1);
