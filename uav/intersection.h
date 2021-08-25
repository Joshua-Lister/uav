#pragma once
#include "test.h"
#include "truck.h"
#include "rural_drone.h"

class intersection
{
	intersection();

	~intersection();
	

	
	double comparison();

	void do_tests();

	double run_truck_tandem_drone(std::string drone_type);

	void run_charging_port_tandem_drone(std::string drone_type);
};

