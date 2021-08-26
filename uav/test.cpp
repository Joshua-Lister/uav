#include "test.h"

bool check_utility_distance()
{
	address_metadata t1, t2;
	t1.x_coord = 3; t1.y_coord = 3;
	t2.x_coord = 6; t2.y_coord = 7;
	double d = util::length(t1, t2);
	if (d == 5)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool check_utility_in()
{
	std::vector<int> int_v = { 1, 2, 5, 10, 200 };
	int dummy = 200;
	bool check = util::in_f(int_v, dummy);
	return check;
}
/*********************************************************************
Calls clustering method check_idsand returns true if all data points 
ids do not equal - 1 and false if at least one id is - 1.
*********************************************************************/
bool check_cluster_ids()
{
	// TRY FIX THIS RUBBISH 
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd, 200);
	cl.run_K_means();
	bool check = cl.check_ids();
	return check;
}
/***********************************************************************************
Reads in actual dataand performs run_K_means then checks the centroid vector 
for repeating locations.Returns true if each location is unique else returns false.
***********************************************************************************/
bool check_for_duplicate_centroid()
{
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd, 200);
	cl.run_K_means();
	Circuit ct(cl);
	bool check = ct.check_truck_route_validity();
	return check;
}

/*********************************************************************
Calls clustering method check_distances.If the distance is more than 
half the maximum drone distance returns false else return true.
*********************************************************************/
bool check_centroids_distance()
{
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd, 200);
	cl.run_K_means();
	//urban_drone ub();
	bool check = cl.check_distances(cl.distances, 10);
	return check;
}

/************************************************************************
Creates two dummy routes that are equaland calls clustering method which 
returns true if the algorithm works as intended as routes are equal and 
false if not.
************************************************************************/
bool check_cluster_stopping_condition()
{
	auto [test_adr1, test_adr2] = setup_adr_v();
	bool check = clustering::stopping_condition(test_adr1, test_adr2);
	return check;
}

std::tuple<std::vector<address_metadata>, std::vector<address_metadata>> setup_adr_v()
{
	size_t test_size = 5;
	std::vector<address_metadata> test_adr1(test_size), test_adr2(test_size);
	float rand_n_x, rand_n_y;
	for (int i = 0; i < test_size; i++)
	{
		rand_n_x = rand() % 100;
		rand_n_y = rand() % 100;
		test_adr1[i].x_coord = rand_n_x;
		test_adr2[i].x_coord = rand_n_x;
		test_adr1[i].y_coord = rand_n_y;
		test_adr2[i].y_coord = rand_n_y;
		test_adr1[i].num = i;
		test_adr2[i].num = i; 
	}
	return make_tuple(test_adr1, test_adr2);
}

/*****************************************************************************
Creates two dummy routes that are equal, mixes one of the routes using the 
Circuit class method.The routes are iterated overand if a location in one 
vector is not equal to another location in the other vector at the same index 
return true else return false.
*****************************************************************************/
bool check_circuit_mix()
{
	auto [test_adr1, test_adr2] = setup_adr_v();
	Circuit c1(test_adr1, false);
	c1.mix(c1.route);
	for (int i = 0; i < c1.route_size; i++)
	{
		if (c1.route[i].num != test_adr2[i].num)
		{
			return true;
		}
	}
	return false;
}

bool GA_optimisation_test_1()
{
	std::fstream myfile;
	myfile.open("Routes.txt", std::fstream::in);
	if (!myfile)
	{
		std::cerr << "Routes.txt could not be opened !\n";
		exit(0);
	}
	std::string line;
	std::vector<double> test_distances;
	while (getline(myfile, line))
	{
		std::stringstream lineStream(line);
		std::string cell;
		std::vector<std::string> parsedRow;
		while (getline(lineStream, cell, ' '))
		{
			parsedRow.push_back(cell);
		}
		test_distances.push_back(std::stoi(parsedRow[parsedRow.size() - 1]));
	}
	bool check = true;
	for (int i = 1; i < test_distances.size(); i++)
	{
		if ((test_distances[i] < test_distances[i - 1]) || (test_distances[i] == test_distances[i - 1]))
			continue;
		else
			check = false;
	}
	return check;
	/*read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd);
	cl.run_K_means();
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, cl);
	result Result = GA_test.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);
	GA_test.*/

	/*genetic_algorithm<Circuit, address_metadata> GA(f, cl);
	GA.run_algorithm_genetic(10, &fitness, &initialise_circuit_v, &check_truck_route_validity);*/

}

/*************************************************************************************
Using the dummy test_route, the mutation function from the genetic_algorithm class 
is called on the route.If the no location appears more than once in the mutated route 
except for the depot then it returns true else returns false.
*************************************************************************************/
bool mutation_test_psm_1()
{
	std::vector<address_metadata> copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	Circuit c1(copy_test_route, false);
	std::default_random_engine generator(lstt.seed);
	GA_test.partial_shuffle_mutation(c1, 1, generator);
	bool check = c1.check_truck_route_validity();
	return check;
}

/*******************************************************************************
Using the dummy test_route, the mutation function from the genetic_algorithm 
class is called on the route.If the mutated route is the same as the original 
result returns false else return true.
*******************************************************************************/
bool mutation_test_psm_2()
{
	std::vector<address_metadata>  copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	Circuit c1(copy_test_route, false);
	std::default_random_engine generator(lstt.seed);
	GA_test.partial_shuffle_mutation(c1, 1, generator);
	int d_track = 0;
	for (int i = 0; i < c1.route_size; i++)
	{
		if (c1.route[i].num == test_route[i].num)
		{
			d_track++;
		}
	}
	if (d_track == c1.route_size)
	{
		return false;
	}
	return true;
}

bool mutation_test_rsm_1()
{
	std::vector<address_metadata> copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	Circuit c1(copy_test_route, false);
	std::default_random_engine generator(lstt.seed);
	GA_test.partial_shuffle_mutation(c1, 1, generator);
	bool check = c1.check_truck_route_validity();
	return check;
}

bool mutation_test_rsm_2()
{
	std::vector<address_metadata>  copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	Circuit c1(copy_test_route, false);
	std::default_random_engine generator(lstt.seed);
	GA_test.partial_shuffle_mutation(c1, 1, generator);
	int d_track = 0;
	for (int i = 0; i < c1.route_size; i++)
	{
		if (c1.route[i].num == test_route[i].num)
		{
			d_track++;
		}
	}
	if (d_track == c1.route_size)
	{
		return false;
	}
	return true;
}

bool mutaiton_test_pm_1()
{
	std::vector<address_metadata> copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	Circuit c1(copy_test_route, false);
	std::default_random_engine generator(lstt.seed);
	GA_test.partial_shuffle_mutation(c1, 1, generator);
	bool check = c1.check_truck_route_validity();
	return check;
}

bool mutaiton_test_pm_2()
{
	std::vector<address_metadata>  copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	Circuit c1(copy_test_route, false);
	std::default_random_engine generator(lstt.seed);
	GA_test.partial_shuffle_mutation(c1, 1, generator);
	int d_track = 0;
	for (int i = 0; i < c1.route_size; i++)
	{
		if (c1.route[i].num == test_route[i].num)
		{
			d_track++;
		}
	}
	if (d_track == c1.route_size)
	{
		return false;
	}
	return true;
}

/**********************************************************************************
Using the dummy test_route, the depot is added to the route.Two - parent and 
two child circuits are initialised the route orders are randomised using Circuit 
member mix.The ordered crossover function is called.The child chromosomes are 
check using the Circuit member check_truck_route_validity.If invalid returns false 
else if both child chromosomes are valid return true.
**********************************************************************************/
bool crossover_test_1()
{
	extern std::vector<address_metadata> test_route;
	std::vector<address_metadata> copy_test_route = test_route;
	address_metadata depot;
	depot.x_coord = 1.3, depot.y_coord = 1.3;
	copy_test_route.push_back(depot);
	copy_test_route.insert(copy_test_route.begin(), depot);
	std::vector<Circuit> c_v(4);
	for (int i = 0; i < 4; i++)
	{
		c_v[i] = Circuit(copy_test_route, false);
		c_v[i].mix(c_v[i].route);
    }
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	std::default_random_engine generator(lstt.seed);
	GA_test.crossover_ordered(c_v[0], c_v[1], c_v[2], c_v[3], 2, 3);
	for (int i = 2; i < 4; i++)
	{
		if (!(c_v[i].check_truck_route_validity()))
		{
			return false;
		}
	}
	return true;
}
bool crossover_test_2()
{
	extern std::vector<address_metadata>  test_route;
	std::vector<address_metadata> copy_test_route = test_route;
	address_metadata depot;
	depot.x_coord = 1.3, depot.y_coord = 1.3;
	copy_test_route.push_back(depot);
	copy_test_route.insert(copy_test_route.begin(), depot);
	std::vector<Circuit> c_v(4);
	for (int i = 0; i < 4; i++)
	{
		c_v[i] = Circuit(copy_test_route, true);
	}
	std::reverse(c_v[1].route.begin(), c_v[1].route.end());
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	std::default_random_engine generator(lstt.seed);
	GA_test.crossover_ordered(c_v[0], c_v[1], c_v[2], c_v[3], 2, 4);
	std::vector<int> child_target_rt1 = { -1, 4, 1, 2, 3, 0, -1 };
	std::vector<int> child_target_rt2 = { -1, 0, 3, 2, 1, 4, -1 };
	for (int adr_idx = 0; adr_idx < c_v[2].route_size; adr_idx++)
	{
		if (c_v[2].route[adr_idx].num != child_target_rt1[adr_idx])
		{
			return false;
		}
		if (c_v[3].route[adr_idx].num != child_target_rt2[adr_idx])
		{
			return false;
		}
	}
	return true;
}

/*************************************************************************************
The genetic_algorithm member run_algorithm_genetic is called and the test_fitness 
function is passed as a parameter.After, each location of the test route is compared 
to the optimal circuit vector computed by the genetic algorithm.
*************************************************************************************/
bool GA_optimisation_test_2()
{
	address_metadata depot;
	depot.x_coord = 1.3, depot.y_coord = 1.3;
	extern std::vector<address_metadata> test_route;
	std::vector<address_metadata>  copy_test_route = test_route;
	/*copy_test_route.push_back(depot);
	copy_test_route.insert(copy_test_route.begin(), depot);*/
	for (int i = 2; i < test_route.size() - 1; i++)
	{
		std::swap(copy_test_route[i], copy_test_route[i - 1]);
	}
	GA_param_list lstt;
	set_GA_params(lstt);
	lstt.max_generation = 200;
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, copy_test_route);
	result Result = GA_test.run_algorithm_genetic(&test_fitness, &initialise_circuit_v, &check_validity_dummy);
	for (int i = 0; i < test_route.size(); i++)
	{
		if (test_route[i].num != Result.circuit_vector[i].num)
		{
			return false;
		}
	}
	return true;
}

void run_tests()
{
	TestClass utility_test("Utility function checks");
	utility_test.test(&check_utility_distance, "Utility distance function");
	utility_test.test(&check_utility_in, "Utility in function");

	TestClass cluster_test("Cluster class checks");
	cluster_test.test(&check_cluster_ids, "Cluster ids");
	cluster_test.test(&check_for_duplicate_centroid, "Duplicate centroid");
	cluster_test.test(&check_centroids_distance, "Cluster distances");
	cluster_test.test(&check_cluster_stopping_condition, "K-Means stopping condition");

	TestClass circuit_test("Circuit class checks");
	circuit_test.test(&check_circuit_mix, "Randomise route");

	TestClass GA_tests("Genetic Algorithm checks");
	GA_tests.test(&mutation_test_rsm_1, "RS Mutation test 1");
	GA_tests.test(&mutation_test_rsm_2, "RS Mutation test 2");
	GA_tests.test(&mutation_test_psm_1, "PS Mutation test 1");
	GA_tests.test(&mutation_test_psm_2, "PS Mutation test 2");
	GA_tests.test(&mutaiton_test_pm_1, "P Mutation test 1");
	GA_tests.test(&mutaiton_test_pm_2, "P Mutation test 2");
	GA_tests.test(&crossover_test_1, "Crossover test 1");
	GA_tests.test(&crossover_test_2, "Crossover test 2");
	GA_tests.test(&GA_optimisation_test_2, "GA test with target route");
	
}