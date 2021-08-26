#pragma once
class truck
{
public:
	truck(double cost_per_litre, int no_of_drones, double fuel_consumption_rate);
	truck(int no_of_drones);
	~truck();
	void set_arrival_time(double t);
	void set_time(double t);
	void set_coords(double x, double y);
	double return_drone_capacity();
	void set_drone_capacity(int dc);
	double travel_cost(double travel_distance);
	double tempus = 0;
	double* x_coord = 0, *y_coord = 0;
	double cost_per_litre = 0, fuel_consumption_rate = 0;

	double tank_capacity = 200; //Liters
	int drone_capacity = 22;


};

