#pragma once
#include "Circuit.h"
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
	vector<int> circuit_vector;
	double optimal_performance;
};

class genetic_algorithm
{
public:
	template <class T, class param_list>
	genetic_algorithm(param_list list, T (*obj_function)(), clustering obj1);
	~genetic_algorithm();
	template <class circumnaviation>
	void crossover(circumnaviation& Circuit1, circumnaviation& Circuit2, circumnaviation& child1, circumnaviation& child2, default_random_engine& generator);
	void calc_fitness(double& max, vector<double>::iterator& max_it, double& min, double& fitness_total, vector<double>& fitness_v);
	void mutation(Circuit& circ, double mutation_prob, std::default_random_engine& generator);
	bool approx_equal(double a, double b, double epsilion);
	int selection(vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator);
	double objective_function();
	double fitness(Circuit& circ1);
	template <class circumnaviation>
	result run_algorithm_genetic();
	int rt_size;
	vector<double> distances;
	vector<Circuit> generation, new_generation;
	clustering obj1;
	GA_param_list lista;
};

