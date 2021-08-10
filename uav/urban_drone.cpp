#include "urban_drone.h"

bool urban_drone::energy_flight_constraint(double L)
{
////, const vector<address_metadata>& depots, const vector<address_metadata>& charging_ports
//
//
//	double energy1 = power_consumption() * (L / horizontal_max_velocity);
//	double min1 = DBL_MAX;
//	size_t cnt = 0;
//	for (auto const& i : depots) {
//		double temp_min = utility::length(i, x_coord, y_coord);
//		if (temp_min < min1) {
//			min1 = temp_min;
//			cnt += 1;
//		}
//	}
//	// restrict depot number based on km squared.
//	double energy2 = power_consumption() * (min1 / horizontal_max_velocity);
//	if (energy1 + energy2 < battery_energy) {
//		battery_energy -= energy1 + energy2;
//		tempus += horizontal_max_velocity / (L + min1); //dsadas
//		this->x_coord = (*depots)[cnt].x_coord; this->y_coord = (*depots)[cnt].y_coord;
//		return true;
//	}
//	min1 = DBL_MAX;
//	cnt = 0;
//	for (auto const& i : *charging_ports) {
//		double temp_min = utility::length(i, x_coord, y_coord);
//		if (temp_min < min1) {
//			min1 = temp_min;
//			cnt += 1;
//		}
//	}
//	// charging port limit of 16 drones, optimise number of depots
//	double energy3 = power_consumption() * (min1 / horizontal_max_velocity);
//	if (energy1 + energy3 < battery_energy) {
//		battery_energy -= energy1 + energy3;
//		tempus += horizontal_max_velocity / (L + min1); //adasdsad
//		this->x_coord = (*charging_ports)[cnt].x_coord; this->y_coord = (*charging_ports)[cnt].y_coord;
//		return true;
//	}
//	else
//		return false;
	return true;
}

		
	

 
