#include "genetic_algorithm.h"

std::uniform_real_distribution<double> rand_number(0, 1.0);

template <class C, class D>
genetic_algorithm<C, D>::genetic_algorithm(GA_param_list lista, std::vector<D>& path) : lista(lista), path(path), rt_size(path.size())
{
}

template <class C, class D>
genetic_algorithm<C, D>::~genetic_algorithm() {}

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

template <class C, class D>
bool genetic_algorithm<C, D>::approx_equal(double a, double b, double eps)
{
	return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * eps);
}


bool operator ==(const address_metadata& c1, const address_metadata& c2)
{
	return (c1.num == c2.num);
}

template <class C, class D>
void genetic_algorithm<C, D>::crossover_ordered(C& parent1, C& parent2, C& child1, C& child2, int a, int b)
{
	// DOES NOT WORK 17/07/21
	//TAKE A LOOK AT THIS FUNCTION
	child1.route.clear(); child2.route.clear();
	child1.route.resize(rt_size); child2.route.resize(rt_size);
	child1.route[0] = parent1.route[0]; child1.route[rt_size - 1] = parent1.route[rt_size - 1];
	child2.route[0] = parent2.route[0]; child2.route[rt_size - 1] = parent2.route[rt_size - 1];

	if (a > b) std::swap(a, b);

	for (int i = a; i < b; i++)
	{
		child1.route[i] = parent1.route[i];
		child2.route[i] = parent2.route[i];
	}


	int j = 1, k = 1;
	for (int i = 1; i < rt_size - 1; i++)
	{
		if (j == a)
		{
			j = b;
		}
		if (!util::find_f(child1.route, parent2.route[i], a, b))
		{
			child1.route[j] = parent2.route[i];
			j++;
		}
		if (k == a)
		{
			k = b;
		}
		if (!util::find_f(child2.route, parent1.route[i], a, b))
		{
			child2.route[k] = parent1.route[i];
			k++;
		}
	}
}

template<class C, class D>
void genetic_algorithm<C, D>::crossover_standard(C& parent1, C& parent2, C& child1, C& child2, int a, int b)
{
	for (int i = 1; i < rt_size - 1; i++)
	{
		// Exchange the numbers of parent1 and parent2 front of the range (a, b)
		if (i < a)
		{
			child2.route[i] = parent1.route[i];
			child1.route[i] = parent2.route[i];
		}


		// Exchange the numbers of parent1 and parent2 rear of the range (a, b)
		else if ((a != b) && (i >= b))
		{
			child2.route[i] = parent1.route[i];
			child1.route[i] = parent2.route[i];
		}

		// Keep the numbers of parent1 and parent2 between the range (a, b)
		else
		{
			child1.route[i] = parent1.route[i];
			child2.route[i] = parent2.route[i];
		}
	}
}


//template <class Circuit>
//void genetic_algorithm::crossover_collision(Circuit& parent1, Circuit& parent2, Circuit& child1, Circuit& child2, default_random_engine& generator)
//{
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
	//}

	//void genetic_algorithm::multi_point_crossover(int no_pivots) 
	//{
	//	vector<int> partitions(no_pivots);
	//	for (int i = 0; i < no_pivots; i++)
	//
	//
	//}
template <class C, class D>
void genetic_algorithm<C, D>::calc_fitness(double& max, std::vector<double>::iterator& max_it,
	double& min, double& fitness_total, std::vector<double>& fitness_v, std::vector<C>& gen)
{
	max_it = std::max_element(fitness_v.begin(), fitness_v.end());
	max = *max_it;
	min = *(std::min_element(fitness_v.begin(), fitness_v.end()));
	for (int i = 0; i < lista.generation_size; i++)
	{
		fitness_v[i] = (fitness_v[i] - min) / (max - min + 1e-6); // max and in are -nan
		fitness_total += fitness_v[i];
	}
}
template <class C, class D>
void genetic_algorithm<C, D>::partial_shuffle_mutation(C& circ, const double mutation_prob, std::default_random_engine& generator)
{
	int idx1, idx2;
	for (int idx = 1; idx < rt_size - 1; idx++)
	{
		double rn = rand_number(generator);
		if (rn < mutation_prob)
		{
			std::uniform_int_distribution<int> randunit(1, rt_size - 2);
			idx1 = randunit(generator);
			do
			{
				idx2 = randunit(generator);
			} while (idx1 == idx2);

			//Circuit::swap_addresses(circ.route, idx1, idx2);
			std::swap(circ.route[idx1], circ.route[idx2]);
		}
	}
}

template<class C, class D>
void genetic_algorithm<C, D>::rs_mutation(C& circ, double mutation_prob, std::default_random_engine& generator)
{
	if (rand_number(generator) < mutation_prob)
	{
		std::uniform_int_distribution<int> randunit(1, rt_size - 2);
		int a = randunit(generator);
		int b;
		do
		{
			b = randunit(generator);
		} while (a == b);
		if (a > b) std::swap(a, b);
		std::reverse((circ.route.begin() + a), (circ.route.begin() + b));
	}
}

template<class C, class D>
void genetic_algorithm<C, D>::point_mutation(C& circ, double mutation_prob, std::default_random_engine& generator)
{
	std::uniform_int_distribution<int> randunit(1, rt_size - 2);
	int a = randunit(generator);
	int b;
	do
	{
		b = randunit(generator);
	} while (a == b);

	std::swap(circ.route[a], circ.route[b]);
}

template <class C, class D>
int genetic_algorithm<C, D>::selection(std::vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator)
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


template <class C, class D>
result genetic_algorithm<C, D>::run_algorithm_genetic(std::function<double(C&)> fitness_func,
	std::function<void(std::vector<C>&, std::vector<C>&, std::vector<C>&, std::vector<D>&, int)> initialise_gen_v, 
	std::function<bool(C&)> eval_circ)
{

#ifdef C_DATA
	vector<double> performance_v;
	vector<vector<D>> track_route_ov;
#endif C_DATA

	std::uniform_int_distribution<int> randunit(1, rt_size - 2);
	std::default_random_engine generator(lista.seed);
	std::uniform_int_distribution<int> randgen(0, lista.generation_size - 1);
	std::vector<C> gen(lista.generation_size + 1), new_gen(lista.generation_size + 1);
	std::vector<double> fitness_v(lista.generation_size);
	std::vector<C> temp_v(2);
	result Result;
	int ind1, ind2;
	int gen_cnt = 0, conv_cnt = 0, n, elite_ind;
	int max_conv_cnt = std::max(100, lista.max_generation / 5);
	double prev_max = -DBL_MAX;
	double fitness_total = 0;


	initialise_gen_v(gen, new_gen, temp_v, path, lista.generation_size); // change this lat one 
	//int max_conv_cnt = max(100, lista.max_generation / 5);
	// reciporcal of fitness remember small distance is better
	double max, min;
	std::vector<double>::iterator max_it;

	while (gen_cnt <= lista.max_generation)
	{
		for (int i = 0; i < lista.generation_size; i++)
			fitness_v[i] = fitness_func(gen[i]);

		calc_fitness(max, max_it, min, fitness_total, fitness_v, gen);
		// Store best performing circuit
		elite_ind = std::distance(fitness_v.begin(), max_it);
		new_gen[0] = gen[elite_ind];
#ifdef C_DATA
		performance_v.push_back(1 / max);
		track_route_ov.push_back(gen[elite_ind].route);
#endif
		if (((1 / max) - (1 / prev_max)) == 0)
		{
			conv_cnt++;
		}
		else
		{
			conv_cnt = 0;
		}
		prev_max = max;

		if ((conv_cnt > max_conv_cnt) || (gen_cnt == lista.max_generation))
		{
			Result.iteration = gen_cnt;
			Result.circuit_vector = gen[elite_ind].route;
			Result.optimal_performance = 1 / max;
			break;
		}

		n = 1;

		while (n < lista.generation_size)
		{
			ind1 = selection(fitness_v, lista.generation_size, fitness_total, generator);
			while (ind2 = selection(fitness_v, lista.generation_size, fitness_total, generator) == ind1);

			double random_number = rand_number(generator);

			if (random_number < lista.crossover_prob)
			{ // change
				int a, b;
				a = randunit(generator);
				while ((b = randunit(generator)) == a);
				crossover_ordered(gen[ind1], gen[ind2], temp_v[0], temp_v[1], a, b);
			}

			else
			{
				temp_v[0] = gen[ind1];
				temp_v[1] = gen[ind2];
			}

			rs_mutation(temp_v[0], lista.mutation_prob, generator);
			rs_mutation(temp_v[1], lista.mutation_prob, generator);

			if (eval_circ(new_gen[n]))
			{
				gen[n] = temp_v[0];
				n++;
			}

			if (eval_circ(new_gen[n]))
			{
				gen[n] = temp_v[1];
				n++;
			}
		}

		gen_cnt++;
		std::swap(gen, new_gen);
	}
#ifdef C_DATA

	size_t route_gen_size = track_route_ov.size();
	size_t perf_v_size = performance_v.size();
	ofstream myfile;
	myfile.open("b_52_routes_rsm.txt");
	myfile << "Route_size" << " " << "Generations " << "Convergence_count " << "Generation_count" << "\n";
	myfile << rt_size << " " << perf_v_size << " " << conv_cnt << " " << gen_cnt << "\n";
	for (int i = 0; i < track_route_ov.size(); i++)
	{
		for (int j = 0; j < track_route_ov[i].size(); j++)
		{
			myfile << track_route_ov[i][j].x_coord << " " << track_route_ov[i][j].y_coord << " ";
		}
		myfile << performance_v[i] << " ";
		myfile << i;
		myfile << std::endl;
	}
	myfile.close();

#endif
	return Result;
}

