#include "drone.h"
drone::drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
	int rotors): maximum_battery_time(maximum_battery_time), maximum_payload_capacity(maximum_payload_capacity), drone_mass(drone_mass),
	payload(payload), max_flight_time(max_flight_time){};

drone::drone() : maximum_battery_time(30), maximum_payload_capacity(5), rotors(6) {};
drone::~drone() {};
// linear energy consumption model that energy consumptions increases linearly with battery and payload weight.
// consume same power whether hovering or flying at constant speed
void drone::set_payload_capacity()
{
	payload = maximum_payload_capacity;
}

//void drone::set_battery_time(){
//	battery_time_remaining = maximum_battery_time;
//}

void drone::set_battery_time(double t) {
	battery_time_remaining -= t;
}

void drone::set_h_velocity_drone(double m_h_v){
	horizontal_max_velocity = m_h_v;
}

void drone::set_v_velocity_drone(double m_v_v)
{
	vertical_max_velocity = m_v_v;
}

bool drone::energy_flight_constraint(double l)
{
	double energy = power_consumption() * (l / horizontal_max_velocity);
	if (energy <= battery_energy) {
		battery_energy -= energy;
		return true;
	}
	else
		return false;
}

double drone::power_consumption()
{
	//vehicle routing problems for drone delivery - https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7513397
	return (pow((this->drone_mass + this->payload), 1.5) * sqrt(9.8 * 9.8 * 9.8 / 2 * fluid_density * disc_area * rotors));
}

double drone::time_to_charge()
{
	//capacity (ah) / charge rate (a)
	return 1.0;
}

void drone::update_battery_time(string bt_condition, double l)
{
	if (bt_condition == "charge" || "charge") {
		battery_time_remaining = maximum_battery_time; // fill in here
		tempus += 0; // fill in here
	}
	else if (bt_condition == "drain" || "drain")
		battery_time_remaining -= energy_flight_constraint(l); // fill in here

	else
		cerr << "failed to enter an appropriate condition. enter either charge or drain";
}

void drone::update_payload(string pd_condition, double weight)
{
	if (pd_condition == "release" || "release")
		payload -= weight; // fill in here

	else if (pd_condition == "load" || "load")
		payload += weight; // fill in here

	else
		cerr << "failed to enter an appropriate condition. enter either release or load";
}

double drone::return_battery_energy_capacity()
{
	return 0; //this->battery_energy_capacity;
}
