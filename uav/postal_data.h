#pragma once
#include <string>
class postal_data
{
	public:
		int id = -1;
		double latitude;
		double longitude;
		std::string out_code;
		std::string in_code;
		bool proximity = false;
		
};

