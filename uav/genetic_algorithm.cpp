#include "genetic_algorithm.h"



template <class T, class param_list>
genetic_algorithm::genetic_algorithm(param_list lista, T(*obj_function)(), clustering obj1) : lista(lista)
{
	vector<double> distances;
	int rt_size = Circuit::route_size;
	
}

uniform_real_distribution<double> rand_number(0, 1.0);
genetic_algorithm::~genetic_algorithm()
{
}

//template <class T, class circumnaviation, class param_list>
//void genetic_algorithm<T, circumnaviation, param_list>::calc_velocities() {
//	for (size_t i = 0; i < Circuit::route_size; i++) {
//		v1[i] = this->.masses[i] - .this->masses[i] / this->.masses[i] + .this->masses[i] * v1[i] +
//			2 * this->.masses[i] / this->.masses[i] + .this->masses[i] * v2[i];
//		v2[i] = 2 * this->.masses[i] / this->.masses[i] + .this->masses[i] * v1[i] - this->.masses[i] -
//			.this->masses[i] / this->.masses[i] + .this->masses[i] * v2[i];
//	}
//}
//genetic_algorithm::calc_standard_deviation(vector<address_metadata>& circ_v)
//
//}
//genetic_algorithm::check_diversity() {
//	double std_sum = 0;
//	for (int )
//}

bool genetic_algorithm::approx_equal(double a, double b, double eps) {
	return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * eps);
}

//operator> ()
template <class circumnaviation>
void genetic_algorithm::crossover(circumnaviation& parent1, circumnaviation& parent2, circumnaviation& child1, circumnaviation& child2, default_random_engine& generator)
{
	for (int i = 0; i < rt_size; i++) 
	{
		if (!approx_equal(parent1.route[i], parent2.route[i])) 
		{
			if (parent1.route[i] > parent2.route[i])
			{
				child1.route[i] = parent1.route[i];
			}
			else 
			{
				child2.route[i] = parent2.route[i];
			}
		}
		else 
		{
			int r = rand() % 2;
			if (r == 0) 
			{
				child1.velocity_v[i] = 0;
				child2.velocity_v[i] = 0;
			}
			else 
			{
			child1.velocity_v[i] = -(parent1.velocity_v[i]);
			child2.velocity_v[i] = -(parent2.velocity_v[i]);
			}
		}
	}
}

void genetic_algorithm::calc_fitness(double& max, vector<double>::iterator& max_it, double& min, double& fitness_total, vector<double>& fitness_v) {
	for (int i = 0; i < lista.generation_size; i++)
		fitness_v[i] = fitness(generation[i]);

	max_it = std::max_element(fitness_v.begin(), fitness_v.end());
	max = *max_it;
	min = *(std::min_element(fitness_v.begin(), fitness_v.end()));
	for (int i = 0; i < lista.generation_size; i++) {
		fitness_v[i] = (fitness_v[i] - min) / (max - min + 1e-6);
		fitness_total += fitness_v[i];
	}
}
void genetic_algorithm::mutation(Circuit& circ, const double mutation_prob, default_random_engine& generator)
{
	
	for (int idx = 0; idx < rt_size; idx++) {
		double rn = rand_number(generator);
		if (rn < mutation_prob) {
			uniform_int_distribution<int> randunit(1, rt_size);
			int idx1 = randunit(generator);
			int idx2;
			while (idx2 = randunit(generator) == idx1);
			Circuit::swap_addresses(circ.route, idx1, idx2);
		}
	}
}

int genetic_algorithm::selection(vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator)
{

	double random_number = rand_number(generator);
	double offset = 0;

	for (int i = 0; i < generation_size; i++)
	{
		offset += fitness_v[i] / fitness_total;
		// subtract small number to avoid getting stuck in environments with no variation
		if (random_number < (offset - 1e-3))
			return i;
	}
	// only used when stuck in environments with no variation
	std::uniform_int_distribution<int> randgen(0, generation_size - 1);
	return randgen(generator);
}

double genetic_algorithm::fitness(Circuit& circ1)
{
	double f = 0;
	for (int i = 1; i < Circuit::route_size - 1; i++)
		f += calc::length(circ1.route[i - 1], circ1.route[i + 1]);
	return f;
}

template <class circumnaviation>
result genetic_algorithm::run_algorithm_genetic()
{
	int seed = 42;
	default_random_engine generator(seed);
	uniform_int_distribution<int> randgen(0, lista.generation_size - 1);
	vector<circumnaviation> gen(lista.generation_size + 1), new_gen(lista.generation_size + 1);
	vector<double> fitness_v(lista.generation_size + 1);
	vector<double> performance_v;

	result Result;
	int ind1, ind2;
	for (int i = 0; i < lista.generation_size; i++) {
		generation[i] = Circuit(obj1.centroids);
	}

	int gen = 0, conv_cnt = 0;
	double prev_max = -DBL_MAX;
	double fitness_total = 0;
	//int max_conv_cnt = max(100, lista.max_generation / 5);
	double max, min;
	vector<double>::iterator max_it;
	while (gen <= lista.max_generation) {
		calc_fitness(max, max_it, min, fitness_total, fitness_v);
		// Store best performing circuit
		int elite_ind = std::distance(fitness_v.begin(), max_it);
		performance_v.push_back(max);

		if (std::abs(max - prev_max) < lista.tolerance)
			conv_cnt++;
		else
			conv_cnt = 0;
		prev_max = max;

		if ((conv_cnt > max_conv_cnt) || (gen == lista.max_generation)) {
			Result.iteration = gen;
			Result.circuit_vector = generation[elite_ind].route;
			Result.optimal_performance = max;
			break;
		}

		int n = 1;
		while (n < lista.generation_size ) {
			ind1 = selection(fitness_v, lista.generation_size, fitness_total, generation);
			while (ind2 == selection(fitness_v, lista.generation_size, fitness_total, generation));

			double rand_number = rand_number(generator);
			if (rand_number < lista.crossover_prob)
				crossover(generation[ind1], generation[ind2], new_generation[n], new_generation[n + 1], generator);
			else {
				new_generation[n] = generation[ind1];
				new_generation[n + 1] = generation[ind2];
			}
			mutation(new_generation[n], lista.mutation_prob, generator);
			mutation(new_generation[n + 1], lista.mutation_prob, generator);
			n = n + 2;

		}
	}
}
