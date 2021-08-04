#pragma once
#include "Circuit.h"
#include "postal_region.h"
#include <cmath>
#include <random>
#include <stdio.h>
#include <algorithm>

struct GA_param_list {
	int num_units, generation_size, max_generation, max_iterations;
	double crossover_prob, mutation_prob, tolerance;
	unsigned seed;
};

struct result {
	int iteration;
	vector<address_metadata> circuit_vector;
	double optimal_performance;
};
//T(*obj_function)()
template <class C>
class genetic_algorithm
{
public:
	// address_metadata& depot, bool unique
	genetic_algorithm(GA_param_list list, clustering obj1);
	genetic_algorithm();
	~genetic_algorithm();
	static double genetic_algorithm::fitness(C& circ1);
	void crossover_collision(C& Circuit1, C& Circuit2, C& child1, C& child2, default_random_engine& generator);
	void calc_fitness(double& max, vector<double>::iterator& max_it, double& min, double& fitness_total, vector<double>& fitness_v, vector<Circuit>& gen);
	void mutation(C& circ, double mutation_prob, std::default_random_engine& generator);
	bool approx_equal(double a, double b, double epsilion);
	void crossover_ordered(C& parent1, C& parent2, C& child1, C& child2, default_random_engine& generator);
	int selection(vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator);
	static void initialise_circuit_v(vector<C>& gen1, vector<C>& gen2, vector<C>& temp_gen);
	result run_algorithm_genetic(int max_conv_cnt, std::function<double(C)> fitness_func,
		std::function<void(C, C, C)> initialise_gen_v);
	int rt_size;
	vector<double> distances;
	vector<Circuit> generation, new_generation;
	clustering obj1;
	GA_param_list lista;
};

