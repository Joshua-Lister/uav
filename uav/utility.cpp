#include "utility.h"
/*******************************
Returns the euclidian distance
********************************/
double util::length(const address_metadata& adr, const address_metadata& centroid) 
{
	return std::sqrt((abs((adr.x_coord - centroid.x_coord) * (adr.x_coord - centroid.x_coord) + (adr.y_coord - centroid.y_coord) * (adr.y_coord - centroid.y_coord))));
}

/*******************************
Returns the euclidian distance
********************************/
double util::length(const address_metadata& adr, const double& x, const double& y)
{
	return abs((adr.x_coord - x) * (adr.x_coord - x) + (adr.y_coord - y) * (adr.y_coord - y));
}

/***********************************************************
Returns true if the supplied element is found in the vector
between index positions start and end
************************************************************/
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

/***********************************************************
Returns true if the supplied element is found in the vector
***********************************************************/
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

/***********************************************************
Returns true if the supplied element is found in the vector
between index positions start and end
***********************************************************/
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

