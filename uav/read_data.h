#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include "postal_region.h"
#include <unordered_map>
using namespace std;
class read_data
{
public:
	read_data(string filename);
	read_data();
	~read_data();

	void read_csv(string filename);
	void fill_data();
	void print_data(string type);
	//std::vector<double> longtitude;
	//std::vector<double> latitude;
	std::vector <std::string> out_code;
	std::vector <std::string> in_code;
	string filename;
	vector<string> post_codes;
	vector<vector<string>> parsedCsv;
	vector<address_metadata> data;
	vector<int> y_coord, x_coord;
	int no_of_addresses = -0;

	//vector<address_metadata> data;
};

