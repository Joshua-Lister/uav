#include "utility.h"
namespace utility
{
	double length(const address_metadata& adr, const address_metadata& centroid) {
		return abs((adr.x_coord - centroid.x_coord) * (adr.x_coord - centroid.x_coord) + (adr.y_coord - centroid.y_coord) * (adr.y_coord - centroid.y_coord));
	}
	double length(const address_metadata& adr, const double& x, const double& y) {
		return abs((adr.x_coord - x) * (adr.x_coord - x) + (adr.y_coord - y) * (adr.y_coord - y));
	}
	// try template this when possible
	bool find(const std::vector<address_metadata>& arg_v, const address_metadata& arg_e, const int start, const int end) {

		for (int i = start; i < end; i++)
			if (arg_v[i].num == arg_e.num)
				return false;
		return true;
	}
}