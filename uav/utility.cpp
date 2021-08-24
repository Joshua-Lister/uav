#include "utility.h"


double util::length(const address_metadata& adr, const address_metadata& centroid) 
{
	return (abs((adr.x_coord - centroid.x_coord) * (adr.x_coord - centroid.x_coord) + (adr.y_coord - centroid.y_coord) * (adr.y_coord - centroid.y_coord)));
}

double util::length(const address_metadata& adr, const double& x, const double& y)
{
	return abs((adr.x_coord - x) * (adr.x_coord - x) + (adr.y_coord - y) * (adr.y_coord - y));
}

bool util::find_f(const std::vector<address_metadata>& arg_v, const address_metadata& arg_e, const int start, const int end)
{

	//for (int i = start; i < end; i++)
	for (int i = start; i < end; i++)
	{
		if (arg_v[i].num == arg_e.num)
		{
			return true;
		}
	}
	return false;
}

bool util::in_f(std::vector<int>& i_v, int subject)
{
	for (int val : i_v)
	{
		if (val == subject)
		{
			return true;
		}
	}
	return false;

}

bool util::in_f(std::vector<address_metadata>& argv, const int s, const int end, address_metadata& argc)
{
	for (int i = s; i < end; i++)
	{
		if (argv[i].num == argc.num)
		{
			return true;
		}
	}
	return false;
}
// stolen from wikipedia
//constexpr float fast_inv_sqrt(const float& val) noexcept {
//	static_assert(std::numeric_limits<float>::is_iec559);
//	float const y = std::bit_cast<float>(0x5f3759df - (std::bit_cast<std::uint32_t>(val) >> 1));
//	return y * (1.5f - (val * 0.5f * y * y));
//}
//void print_f();
