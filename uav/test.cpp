#include "test.h"
#pragma once

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
	clustering::stopping_condition(test_adr1, test_adr2);
	return false;
}

bool GA_optimisation_test_1()
{
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd);
	cl.run_K_means();

	genetic_algorithm<Circuit, address_metadata> GA(f, cl);
	GA.run_algorithm_genetic(10, &fitness, &initialise_circuit_v, &check_truck_route_validity);

	return false;
}
