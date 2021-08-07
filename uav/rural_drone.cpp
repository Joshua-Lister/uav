#include "rural_drone.h"

bool rural_drone::energy_flight_constraint(double L)
{
	double energy1 = power_consumption() * (L / horizontal_max_velocity);
	double dist_to_truck = utility::length(adr, this->x_coord, this->y_coord);
	return true;
}
