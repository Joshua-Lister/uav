#pragma once
#include "postal_region.h"
#include <vector>
#include <bit>
#include <limits>
#include <cstdint>
namespace utility
{
	double length(const address_metadata& adr, const address_metadata& centroid);
	double length(const address_metadata& adr, const double& x, const double& y);
	//template <class container, class T>
	bool find(const vector<address_metadata>& arg_v, const address_metadata& arg_e, const int start, const int end);
	/*constexpr float fast_inv_sqrt(const float& val) noexcept;*/
}