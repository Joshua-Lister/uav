#pragma once
using namespace std;
#include <string>
#include <iostream>
#include "clustering.h"
class drone
{
public:
	bool battery_swap;
	string battery_type;
	double battery_energy = -1;
	inline static double maxiumum_distance;
	bool out_of_use = false;
protected:
	double battery_time_remaining;
	double payload;
	double drone_mass;
	double motor_power;
	const double max_flight_time = 30;
	double arrival_time;
	double tempus = 0;
	double x_coord, y_coord;
	double battery_energy_capacity = -1;
	double maximum_payload_capacity = -1;;
	double horizontal_max_velocity = -1;
	double vertical_max_velocity = -1;
	double maximum_battery_time = -1;
	double charge_time = -1;
	double fluid_density = -1; // kg/m^3
	double disc_area = -1;
	int rotors = -1;
	vector<address_metadata> route;


public:
	drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
		int rotors);
	drone();
	~drone();
	void set_h_velocity_drone(double m_h_v);
	void set_v_velocity_drone(double m_v_v);
	bool virtual energy_flight_constraint(double L) = 0;
	double time_to_charge();
	double power_consumption();
	void set_battery_time(double t);
	void set_payload_capacity();
	void update_battery_time(string bc_condition, double L);
	void update_payload(string pd_condition, double weight);
	static double return_battery_energy_capacity();
	 
};

