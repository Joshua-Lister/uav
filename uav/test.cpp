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

bool check_centroids_visited()
{
	return false;
}

bool check_cluster_stopping_condition()
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
	}
	bool check = clustering::stopping_condition(test_adr1, test_adr2);
	return check;
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
	TestClass test_software("Drone Delivery Software");
	test_software.test(&check_cluster_ids, "Cluster ids");
	test_software.test(&check_for_duplicate_centroid, "Duplicate centroid");
	test_software.test(&check_cluster_stopping_condition, "K-Means Stopping Condition");
	test_software.test(&GA_optimisation_test_2, "GA test with target route");
	
}