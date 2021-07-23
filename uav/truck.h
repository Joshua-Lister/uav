#pragma once
class truck
{
public:
	void set_arrival_time(double t);
	void set_time(double t);
	void set_coords(double x, double y);
	double return_drone_capacity();
	void set_drone_capacity(double dc);
	double tempus = 0;
	double x_coord = 0, y_coord = 0;

	size_t drone_capacity = 0;


};

