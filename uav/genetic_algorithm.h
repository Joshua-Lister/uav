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
class genetic_algorithm
{
public:

	genetic_algorithm(GA_param_list list, clustering obj1);
	genetic_algorithm();
	~genetic_algorithm();
	//template <class Circuit>
	void crossover_collision(Circuit& Circuit1, Circuit& Circuit2, Circuit& child1, Circuit& child2, default_random_engine& generator);
	void calc_fitness(double& max, vector<double>::iterator& max_it, double& min, double& fitness_total, vector<double>& fitness_v, vector<Circuit>& gen);
	void mutation(Circuit& circ, double mutation_prob, std::default_random_engine& generator);
	bool approx_equal(double a, double b, double epsilion);
	//template <class Circuit>
	void crossover_ordered(Circuit& parent1, Circuit& parent2, Circuit& child1, Circuit& child2, default_random_engine& generator);
	int selection(vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator);
	double objective_function();
	double fitness(Circuit& circ1);
	//template <class Circuit>
	result run_algorithm_genetic(int max_conv_cnt);
	int rt_size;
	vector<double> distances;
	vector<Circuit> generation, new_generation;
	clustering obj1;
	GA_param_list lista;
};

