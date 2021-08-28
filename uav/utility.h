#pragma once
#include "postal_region.h"
#include <vector>
#include <cmath>
class util
{
public:
	static double length(const address_metadata& adr, const address_metadata& centroid);
	static double length(const address_metadata& adr, const double& x, const double& y);
	//template <class T>
	static bool find_f(const std::vector<address_metadata>& arg_v, const address_metadata& arg_e, const int start, const int end);
	static bool in_f(std::vector<int>& i_v, int subject);
	/*constexpr float fast_inv_sqrt(const float& val) noexcept;*/
	static bool in_f(std::vector<address_metadata>& argv, const int s, const int end, address_metadata& argc);
};