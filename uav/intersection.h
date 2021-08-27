#pragma once
#include "test.h"
#include "flight.h"


class intersection
{
public:
	intersection();

	~intersection();

	static void set_GA_params_list(GA_param_list& lst);

	void set_parameters(double& elec_cost, double& fuel_cost, double& max_flight_distance, double& max_payload, int& truck_vol_capacity, std::string drone_choice);

	void run_which_linux();

	void run_which_windows(std::string choice);
};

