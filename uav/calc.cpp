#include "calc.h"
namespace calc
{
	double length(const address_metadata& adr, const address_metadata& centroid) {
		return abs((adr.x_coord - centroid.x_coord) * (adr.x_coord - centroid.x_coord) + (adr.y_coord - centroid.y_coord) * (adr.y_coord - centroid.y_coord));
	}
	double length(const address_metadata& adr, const double& x, const double& y) {
		return abs((adr.x_coord - x) * (adr.x_coord - x) + (adr.y_coord - y) * (adr.y_coord - y));
	}
}