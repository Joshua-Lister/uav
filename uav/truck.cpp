#include "truck.h"

truck::truck(double cost_per_litre, int no_of_drones, double fuel_consumption_rate){}
//truck::truck(int no_of_drones) : cost_per_litre(1.13), fuel_consumption_rate(0.35){}
truck::truck(int no_of_drones){}
truck::~truck(){}

void truck::set_arrival_time(double t)
{
}

void truck::set_time(double t)
{
}

void truck::set_coords(double x, double y)
{
	//this->x_coord = x;
	//this->y_coord = y;
}

double truck::return_drone_capacity(){
	return this->drone_capacity;
}

void truck::set_drone_capacity(int dc){
	this->drone_capacity = dc;
}


