#pragma once
#include <string>
struct address_metadata
{
	std::string post_code;
	double x_coord = 0, y_coord = 0;
	std::string out_code;
	std::string in_code;
	int id = -1;
	bool visited = false;
	int num = -1;
	int parcel_mass = 0, no_of_parcels = 0;
	double mass = 0;
	bool depot = false;

};