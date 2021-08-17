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
template <class C, class D>
class genetic_algorithm
{
public:
	// address_metadata& depot, bool unique
	genetic_algorithm(GA_param_list list, clustering obj1);
	//genetic_algorithm(GA_param_list lista, string target_str);
	~genetic_algorithm();
	//static double fitness(Circuit& circ1);
	void crossover_collision(vector<C>& Circuit1, vector<C>& Circuit2, vector<C>& child1, vector<C>& child2, default_random_engine& generator);
	void calc_fitness(double& max, vector<double>::iterator& max_it, double& min, double& fitness_total, vector<double>& fitness_v, vector<Circuit>& gen);
	void mutation(C& circ, double mutation_prob, std::default_random_engine& generator);
	bool approx_equal(double a, double b, double epsilion);
	void crossover_ordered(C& parent1, C& parent2, C& child1, C& child2, default_random_engine& generator);
	int selection(vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator);
	//static void initialise_circuit_v(vector<C>& gen1, vector<C>& gen2, vector<C>& temp_gen);
	result run_algorithm_genetic(int max_conv_cnt, std::function<double(C&)> fitness_func,
		std::function<void(vector<C>&, vector<C>&, vector<C>&, vector<D>&, int)> initialise_gen_v, std::function<bool(C&)> eval_circ);
	// does it need to be vector d
	int rt_size;
	clustering obj1;
	//vector<double> distances;
	vector<C> generation, new_generation;
	GA_param_list lista;
#ifdef TEST
	vector<double> performance_v;
	vector<vector<C>> track_route_ov_g;
#endif
};


template class genetic_algorithm<Circuit, address_metadata>;
genetic_algorithm<Circuit, address_metadata>::genetic_algorithm(GA_param_list list, clustering obj1);
void genetic_algorithm<Circuit, address_metadata>::crossover_ordered(Circuit& parent1, Circuit& parent2, Circuit& child1, Circuit& child2, default_random_engine& generator);
int  genetic_algorithm<Circuit, address_metadata>::selection(vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator);
void genetic_algorithm<Circuit, address_metadata>::calc_fitness(double& max, vector<double>::iterator& max_it, double& min, double& fitness_total, vector<double>& fitness_v, vector<Circuit>& gen);
result genetic_algorithm<Circuit, address_metadata>::run_algorithm_genetic(int max_conv_cnt, std::function<double(Circuit&)> fitness_func,
	std::function<void(vector<Circuit>&, vector<Circuit>&, vector<Circuit>&, vector<address_metadata>&, int)> initialise_gen_v, std::function<bool(Circuit&)> eval_circ);
//template class genetic_algorithm<string, string>; // change