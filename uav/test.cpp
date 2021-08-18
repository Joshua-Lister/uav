#include "test.h"


bool check_cluster_ids()
{
	// TRY FIX THIS RUBBISH 
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd);
	cl.run_K_means();
	bool check = cl.check_ids();
	return check;
}

bool check_for_duplicate_centroid()
{
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd);
	cl.run_K_means();
	Circuit ct(cl);
	bool check = ct.check_truck_route_validity();
	return check;
}

bool check_centroids_distance()
{
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd);
	cl.run_K_means();
	urban_drone ub();
	bool check = cl.check_distances(cl.distances, 10);
	return check;
}

bool check_cluster_stopping_condition()
{
	auto [test_adr1, test_adr2] = setup_adr_v();
	bool check = clustering::stopping_condition(test_adr1, test_adr2);
	return check;
}
std::tuple<vector<address_metadata>, vector<address_metadata>> setup_adr_v()
{
	size_t test_size = 5;
	vector<address_metadata> test_adr1(test_size), test_adr2(test_size);
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
	fstream myfile;
	myfile.open("Routes.txt", fstream::in);
	if (!myfile)
	{
		std::cerr << "Routes.txt could not be opened !\n";
		exit(0);
	}
	std::string line;
	vector<double> test_distances;
	while (getline(myfile, line))
	{
		std::stringstream lineStream(line);
		string cell;
		vector<string> parsedRow;
		while (getline(lineStream, cell, ' '))
		{
			parsedRow.push_back(cell);
		}
		test_distances.push_back(stoi(parsedRow[parsedRow.size() - 1]));
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
	result Result = GA_test.run_algorithm_genetic(10, &fitness, &initialise_circuit_v, &check_truck_route_validity);
	GA_test.*/

	/*genetic_algorithm<Circuit, address_metadata> GA(f, cl);
	GA.run_algorithm_genetic(10, &fitness, &initialise_circuit_v, &check_truck_route_validity);*/

}

bool mutation_test_1()
{
	extern clustering test_route;
	clustering copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, test_route);
	Circuit c1(test_route);
	default_random_engine generator(lstt.seed);
	GA_test.mutation(c1, 1, generator);
	bool check = c1.check_truck_route_validity();
	return check;
}

bool mutation_test_2()
{
	extern clustering test_route;
	clustering copy_test_route = test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, test_route);
	Circuit c1(test_route);
	default_random_engine generator(lstt.seed);
	GA_test.mutation(c1, 1, generator);
	int d_track = 0;
	for (int i = 0; i < c1.route_size; i++)
	{
		if (c1.route[i].num == copy_test_route.centroids[i].num) 
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
bool crossover_test()
{
	extern clustering test_route;
	clustering copy_test_route = test_route;
	vector<Circuit> c_v(4);
	for (int i = 0; i < 4; i++)
	{
		c_v[i] = Circuit(test_route.centroids, false);
		c_v[i].mix(c_v[i].route);
	}
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, test_route);
	default_random_engine generator(lstt.seed);
	GA_test.crossover_ordered(c_v[0], c_v[1], c_v[2], c_v[3], generator);
	for (int i = 2; i < 4; i++)
	{
		if (!(c_v[i].check_truck_route_validity()))
		{
			return false;
		}
	}
	return true;
}
bool GA_optimisation_test_2()
{
	extern clustering test_route;
	GA_param_list lstt;
	set_GA_params(lstt);
	genetic_algorithm<Circuit, address_metadata> GA_test(lstt, test_route);
	result Result = GA_test.run_algorithm_genetic(5, &test_fitness, &initialise_circuit_v, &check_validity_dummy);
	for (int i = 0; i < test_route.centroids.size(); i++)
	{
		if (test_route.centroids[i].num != Result.circuit_vector[i].num)
		{
			return false;
		}
	}
	return true;
}

void run_tests()
{
	TestClass cluster_test("Cluster class checks");
	cluster_test.test(&check_cluster_ids, "Cluster ids");
	cluster_test.test(&check_for_duplicate_centroid, "Duplicate centroid");
	cluster_test.test(&check_centroids_distance, "Cluster distances");
	cluster_test.test(&check_cluster_stopping_condition, "K-Means stopping condition");
	
	TestClass circuit_test("Circuit class checks");
	circuit_test.test(&check_circuit_mix, "Randomise route");
	TestClass GA_tests("Genetic Algorithm checks");
	GA_tests.test(&GA_optimisation_test_2, "GA test with target route");
	GA_tests.test(&mutation_test_1, "Mutation test 1");
	GA_tests.test(&mutation_test_2, "Mutation test 2");
	GA_tests.test(&crossover_test, "Crossover test");
	
}