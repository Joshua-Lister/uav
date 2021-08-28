#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include "postal_region.h"
#include <vector>
#include <unordered_map>
class read_data
{
public:
	read_data(std::string filename);
	read_data();
	~read_data();

	void read_csv();
	void fill_data();
	void print_data(std::string type);
	//std::vector<double> longtitude;
	//std::vector<double> latitude;
	std::vector <std::string> out_code;
	std::vector <std::string> in_code;
	std::string filename;
	std::vector<std::string> post_codes;
	std::vector<std::vector<std::string>> parsedCsv;
	std::vector<address_metadata> data;
	std::vector<int> y_coord, x_coord;
	int no_of_addresses = 0;
	int total_parcel_mass = 0;

	//vector<address_metadata> data;
};

