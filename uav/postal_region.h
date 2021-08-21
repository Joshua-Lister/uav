#pragma once
#include <string>
using namespace std;
struct address_metadata
{
	string post_code;
	double x_coord = 0, y_coord = 0;
	string out_code;
	string in_code;
	int id = -1;
	bool visited = false;
	int num = -1;
	int parcel_mass = 0, no_of_parcels = 0;
	double mass = 0;
	bool depot = false;

};