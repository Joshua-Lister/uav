#pragma once
#include "postal_region.h"
namespace calc
{
	double length(const address_metadata& adr, const address_metadata& centroid);
	double length(const address_metadata& adr, const double& x, const double& y);
}