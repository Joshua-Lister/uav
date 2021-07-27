#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include "clustering.h"
#include "Circuit.h"
#include "genetic_algorithm.h"
#include <chrono>
//using namespace std;

int main()
{
	read_data tets("postal_data.txt");
	tets.fill_data();
	tets.print_data("All");
	//cout << tets.data[0].y_coord<<  "\n";
	//cout << "hi\n";
	clustering cl(1, 4, tets);
	cl.set_rand_centroids();
	cl.K_means(); // problem with this func
	GA_param_list f;
	f.generation_size = 5;
	f.crossover_prob = 0.5;
	f.max_iterations = 30;
	f.mutation_prob = 0.1;
	f.seed = std::chrono::system_clock::now().time_since_epoch().count();;
	f.tolerance = 1.0e-3;

	genetic_algorithm vb(f, cl);
	vb.run_algorithm_genetic(10);
	//cl.run_K_means();
	//Circuit tt(cl);
	return 0;
}