#pragma once
#include "genetic_algorithm.h"
#include "test.h"

class intersection
{
	intersection();

	void set_GA_params(GA_param_list& lst);
	
	void do_tests();

	double run_truck_tandem_drone(string drone_type);
};

