#include "genetic_algorithm.h"


genetic_algorithm::genetic_algorithm(GA_param_list lista,  clustering obj1) : lista(lista), obj1(obj1)
{
	rt_size = obj1.centroids.size();
	/*if (unique)
	{
		obj1.centroids.push_back(depot);
		obj1.centroids.insert(obj1.centroids.begin(), depot);
	}*/
}
genetic_algorithm::genetic_algorithm() {};
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
// template class class__<int>
bool operator ==(const address_metadata& c1, const address_metadata& c2)
{
	return (c1.num == c2.num);
}
//template <class Circuit>
void genetic_algorithm::crossover_ordered(Circuit& parent1, Circuit& parent2, Circuit& child1, Circuit& child2, default_random_engine& generator)
{
	int a, b;
	//while ((a = rand() % rt_size - 1) == (b = rand() % rt_size - 1));
	uniform_int_distribution<int> randunit(1, rt_size - 1);
	a = randunit(generator);
	while ((b = randunit(generator)) == a && b == a - 1 && b == a + 1);

	if (a > b) swap(a, b);
	// something
	
	for (int i = a; i < b; i++) {
		child1.route[i] = parent1.route[i]; 
		child2.route[i] = parent2.route[i];
		}
	
	
	//shortest difference between any pairs of routes. Find shortest route between one point on graph and another 
	for (int i = 0; i < a; i++) {
		
		if (utility::find(child1.route, parent2.route[i], a, b))
			child1.route[i] = parent2.route[i];
		
		if (utility::find(child2.route, parent1.route[i], a, b))
			child2.route[i] = parent1.route[i];
	}
	for (int i = b; i < rt_size; i++) {
		
		if (utility::find(child1.route, parent2.route[i], a, b))
			child1.route[i] = parent2.route[i];
		
		if (utility::find(child2.route, parent1.route[i], a, b))
			child2.route[i] = parent1.route[i];
	}
}
//operator> ()
//template <class Circuit>
void genetic_algorithm::crossover_collision(Circuit& parent1, Circuit& parent2, Circuit& child1, Circuit& child2, default_random_engine& generator)
{
	/*for (int i = 0; i < rt_size; i++) 
	{
		if (!approx_equal(parent1.route[i], parent2.route[i], 1e-6) 
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
	}*/
}

//void genetic_algorithm::multi_point_crossover(int no_pivots) 
//{
//	vector<int> partitions(no_pivots);
//	for (int i = 0; i < no_pivots; i++)
//
//
//}
void genetic_algorithm::calc_fitness(double& max, vector<double>::iterator& max_it, double& min, double& fitness_total, vector<double>& fitness_v, vector<Circuit>& gen) 
{
	for (int i = 0; i < lista.generation_size; i++)
		fitness_v[i] = fitness(gen[i]);

	max_it = std::max_element(fitness_v.begin(), fitness_v.end());
	max = *max_it;
	min = *(std::min_element(fitness_v.begin(), fitness_v.end()));
	for (int i = 0; i < lista.generation_size; i++) {
		fitness_v[i] = (fitness_v[i] - min) / (max - min + 1e-6); // max and in are -nan
		fitness_total += fitness_v[i];
	}
	for (auto i : fitness_v)
		cout << i << "\t";
	cout << "\n";
}
void genetic_algorithm::mutation(Circuit& circ, const double mutation_prob, default_random_engine& generator)
{
	int idx1, idx2;
	for (int idx = 0; idx < rt_size; idx++) {
		double rn = rand_number(generator);
		if (rn < mutation_prob) {
			uniform_int_distribution<int> randunit(1, rt_size - 1);
			idx1 = randunit(generator);
			while ((idx2 = randunit(generator)) == idx1); // here
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


//template <class Circuit>
result genetic_algorithm::run_algorithm_genetic(int max_conv_cnt, double (*fitness_func)(Circuit))
{
	//lista.generation_size++;
	default_random_engine generator(lista.seed);
	uniform_int_distribution<int> randgen(0, lista.generation_size - 1);
	vector<Circuit> gen(lista.generation_size + 1), new_gen(lista.generation_size + 1);
	vector<double> fitness_v(lista.generation_size + 1);
	vector<double> performance_v;
	vector<Circuit> temp_v(2);
	result Result;
	int ind1, ind2;
	for (int i = 0; i < lista.generation_size + 1; i++) {
		gen[i] = Circuit(obj1.centroids, false); 
		new_gen[i] = Circuit(obj1.centroids, true);
	}
	for (int i = 0; i < temp_v.size(); i++)
		temp_v[i] = Circuit(obj1.centroids, true);

	int gen_cnt = 0, conv_cnt = 0, n, elite_ind;
	double prev_max = -DBL_MAX;
	double fitness_total = 0;
	//int max_conv_cnt = max(100, lista.max_generation / 5);
	// reciporcal of fitness remember small distance is better
	double max, min;
	vector<double>::iterator max_it;
	while (gen_cnt <= lista.max_generation) {
		calc_fitness(max, max_it, min, fitness_total, fitness_v, gen);
		// Store best performing circuit
		elite_ind = std::distance(fitness_v.begin(), max_it);
		performance_v.push_back(max);

		if (std::abs(max - prev_max) < lista.tolerance)
			conv_cnt++;
		else
			conv_cnt = 0;
		prev_max = max;

		if ((conv_cnt > max_conv_cnt) || (gen_cnt == lista.max_generation)) {
			Result.iteration = gen_cnt;
			Result.circuit_vector = gen[elite_ind].route; // fails here 
			Result.optimal_performance = max;
			break;
		}

		n = 1;
		while (n < lista.generation_size) {
			ind1 = selection(fitness_v, lista.generation_size, fitness_total, generator);
			while (ind2 = selection(fitness_v, lista.generation_size, fitness_total, generator) == ind1);
			double random_number = rand_number(generator);
			if (0 < lista.crossover_prob)
				crossover_ordered(gen[ind1], gen[ind2], temp_v[0], temp_v[1], generator);
			else {
				temp_v[0] = gen[ind1];
				temp_v[1] = gen[ind2];
				}
				mutation(temp_v[0], lista.mutation_prob, generator);
				mutation(temp_v[1], lista.mutation_prob, generator);
				if (new_gen[n].check_truck_route_validity(false)) {
					gen[n] = temp_v[0];
					n++;
				}
				if (new_gen[n + 1].check_truck_route_validity(false)) {
					gen[n] = temp_v[1];
					n++;
				}
			}
		gen_cnt++;
		swap(gen, new_gen);
		}
	return Result;
	}
