#pragma once

#include <string>
#include <iostream>
#include "clustering.h"
#include "utility.h"
#include <functional>


class drone
{
public:
	bool battery_swap;
	std::string battery_type;
	double battery_energy = -1;
	bool out_of_use = false;
protected:
	double battery_time_remaining;
	double payload;
	double drone_mass;
	double max_flight_time;
	double motor_power;
	double arrival_time;
	double tempus = 0;
	double x_coord, y_coord;
	double battery_energy_capacity = -1;
	double horizontal_max_velocity = -1;
	double vertical_max_velocity = -1;
	double maximum_battery_time = -1;
	double charge_time = -1;
	double fluid_density = -1; // kg/m^3
	double disc_area = -1;
	int rotors = -1;
	std::vector<address_metadata> route;


public:
	drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
		int rotors);
	drone(double payload, double max_flight_time);
	drone();
	~drone();
	void set_h_velocity_drone(double m_h_v);
	void set_v_velocity_drone(double m_v_v);
	//virtual bool energy_flight_constraint(double L) = 0;

	virtual bool energy_flight_constraint(double L) = 0;
	virtual std::tuple<int, int, int, int> drone_multi_delivery(int k, int ad_adr, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route, double max_payload_cap,
		double max_dist) = 0;
	//virtual void set_up_drones(int number_of_drones) = 0;
	double time_to_charge();
	double power_consumption();
	void set_battery_time(double t);
	//void set_payload_capacity();
	void update_battery_time(std::string bc_condition, double L);
	void update_payload(std::string pd_condition, double weight);
	static double return_battery_energy_capacity();

	double maxiumum_distance = 200;
	double maximum_payload_capacity = 5;
};

