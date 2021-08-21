#include "genetic_algorithm.h"

template <class C, class D>
genetic_algorithm<C, D>::genetic_algorithm(GA_param_list lista,  clustering obj1) : lista(lista), obj1(obj1)
{
	rt_size = obj1.centroids.size();
}

//template <class C, class D>
//genetic_algorithm<C, D>::genetic_algorithm(GA_param_list lista, string target_str) :lista(lista)
//{
//
//	rt_size = target_str.size();
//
//};
uniform_real_distribution<double> rand_number(0, 1.0);

template <class C, class D>
genetic_algorithm<C, D>::~genetic_algorithm(){}

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
// template class class__<int>
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
	//int s = rt_size - (b - a);
	child1.route.resize(rt_size); child2.route.resize(rt_size);
	child1.route[0] = parent1.route[0]; child1.route[rt_size - 1] = parent1.route[rt_size - 1];
	child2.route[0] = parent2.route[0]; child2.route[rt_size - 1] = parent2.route[rt_size - 1];
	//while ((a = rand() % rt_size - 1) == (b = rand() % rt_size - 1));
	//uniform_int_distribution<int> randunit(1, rt_size - 2);
	//a = randunit(generator);
	////while ((b = randunit(generator)) == a && b == a - 1 && b == a + 1);
	//while ((b = randunit(generator)) == a);

	if (a > b) swap(a, b);
	// something
	/*vector<D> slice1(b - a);
	vector<D> slice2(b - a);
	int k = 0;
	for (int j = a; j < b; j++)
	{
		slice1[k] = parent1.route[j];
		k++;
	}*/
	for (int i = a; i < b; i++)
	{
		child1.route[i] = parent1.route[i];
		child2.route[i] = parent2.route[i];
	}
	/*cout << "parent 1 : ";*/
	//for (int i = 1; i < rt_size - 1; i++)
	//{
	//	cerr << parent1.route[i].num << " ";

	//}
	//cout << "\nparent 2 : ";
	//for (int i = 1; i < rt_size - 1; i++)
	//{
	//	cerr << parent2.route[i].num << " ";
	//}
	//cout << "\nchild1 slice : ";
	//for (int i = a; i < b; i++)
	//{
	//	cerr << child1.route[i].num << " ";
	//}
	//cout << "\nchild2 slice : ";
	//for (int i = a; i < b; i++)
	//{
	//	cerr << child2.route[i].num << " ";
	//}
	/*int j = 0;
	for (int i = a; i < b; i++)
	{
		slice_ptr1[j] = &parent1.route[i];
		slice_ptr2[j] = &parent2.route[i];
	}*/
	/*cout << "parent 1 : ";
	for (int i = 1; i < rt_size - 1; i++)
	{
		cerr << parent1.route[i].num << " ";

	}
	cout << "\nparent 2 : ";
	for (int i = 1; i < rt_size - 1; i++)
	{
		cerr << parent2.route[i].num << " ";
	}
	cout << "\nchild 1 : ";
	for (int i = 1; i < rt_size - 1; i++)
	{
		cerr << child1.route[i].num << " ";
	}
	cout << "\n";*/
	////shortest difference between any pairs of routes. Find shortest route between one point on graph and another
	//for (int i = 1; i < a; i++) 
	//{
	//	int j = i;
	//	while (child1.route[i].num == -1)
	//	{
	//		if (utility::find(child1.route, parent2.route[j], a, b))
	//		{
	//			child1.route[i] = parent2.route[j];
	//			break;
	//		}
	//		j++;

	//	}
	//	while (child2.route[i].num == -1)
	//	{
	//		if (utility::find(child2.route, parent1.route[j], a, b))
	//		{
	//			child2.route[i] = parent1.route[j];
	//			break;
	//		}
	//		j++;
	//	}
	//}
	//for (int i = b; i < rt_size; i++) 
	//{
	//	
	//	if (utility::find(child1.route, parent2.route[i], a, b))
	//		child1.route[i] = parent2.route[i];
	//	
	//	if (utility::find(child2.route, parent1.route[i], a, b))
	//		child2.route[i] = parent1.route[i];
	////}
	//int i = 1, pos = 0;
	//while (i < rt_size - 1)
	//{
	//	if (utility::find(child1.route, parent2.route[i], a, b))
	//	{
	//		child1.route[i] = parent2.route[i];
	//		i++;
	//	}
	//	else
	//	{
	//		while (!utility::find(child1.route, parent2.route[i], a, b))
	//		{
	//			i++;
	//		}
	//		child1.route[i] = parent2.route[i];
	//		i++;
	//	}

	//}
	/*int idx1 = -1, idx2 = -1;
	vector<int> index_track1(rt_size - 1);
	vector<int> index_track2(rt_size - 1);
	int pos1 = 0, pos2 = 0;
	for (int i = a; i < b; i++)
	{
		if (utility::find(parent2.route, child1.route[i], 1, (rt_size - 1), idx1))
		{
			index_track1[i] = idx1;
		}
		if (utility::find(parent1.route, child2.route[i], 1, (rt_size - 1), idx2))
		{
			index_track2[i] = idx2;
		}
	}
	int j = 1;
	for (int i = 1; i < a + 1; i++)
	{
		while (utility::in(index_track1, i))
		{
			i++;
		}
		child1.route[j] = parent2.route[i];
		j++;
	}
	j = b;
	for (int i = b; i < rt_size - 1; i++)
	{
		while (utility::in(index_track1, i))
		{
			i++;
		}
		child1.route[j] = parent2.route[i];
		j++;
	}*/
	//for (int i = 1; i < rt_size - 1; i++)
	//{
	//	if (utility::in(index_track2, i))
	//	{
	//		continue;
	//	}
	//	else
	//	{
	//		child2.route[i] = parent1.route[i];
	//	}
	//}

	/*for (int i = 1; i < rt_size - 1; i++)
	{
		int dx = (b - 1 + i) % (rt_size - 1);
	}*/
	/*int j = 1;
	for (int i = 1; i < a; i++)
	{
		while (utility::in(child1.route, a, b, parent2.route[i]))
		{
			i++;
		}
		child1.route[j] = parent2.route[i];
		j++;
	}
	j = b;
	for (int i = b; i < rt_size - 1; i++)
	{
		while (utility::in(child1.route, a, b, parent2.route[i]))
		{
			i++;
		}
		child1.route[j] = parent2.route[i];
		j++;
	}*/
	/*for (int i = 1; i < rt_size - 1; i++)
	{
		if (!utility::in(slice1, 0, slice1.size(), parent2.route[i]))
		{
			child1.route[i] = parent2.route[i];
		}
		if (i == a)
		{
			child1.route.insert(child1.route.end(), slice1.begin(), slice1.end());
			s = child1.route.size();
		}
	}*/
int j = 1, k = 1;
	for (int i = 1; i < rt_size - 1; i++)
	{
		if (j == a)
		{
			j = b;
		}
		if (!utility::find(child1.route, parent2.route[i], a, b))
		{
			child1.route[j] = parent2.route[i];
			j++;
		}
		if (k == a)
		{
			k = b;
		}
		if (!utility::find(child2.route, parent1.route[i], a, b))
		{
			child2.route[k] = parent1.route[i];
			k++;
		}
	}

	/*cout << "\nchild 1 : ";
	for (int i = 1; i < rt_size - 1; i++)
	{
		cerr << child1.route[i].num << " ";
	}
	cout << "\nchild 2 : ";
	for (int i = 1; i < rt_size - 1; i++)
	{
		cerr << child2.route[i].num << " ";
	}
	cout << "\n";*/
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
void genetic_algorithm<C, D>::calc_fitness(double& max, vector<double>::iterator& max_it, 
	double& min, double& fitness_total, vector<double>& fitness_v, vector<Circuit>& gen)
{
	max_it = std::max_element(fitness_v.begin(), fitness_v.end());
	max = *max_it;
	min = *(std::min_element(fitness_v.begin(), fitness_v.end()));
	for (int i = 0; i < lista.generation_size; i++) 
	{
		fitness_v[i] = (fitness_v[i] - min) / (max - min + 1e-6); // max and in are -nan
		fitness_total += fitness_v[i];
	}
	/*for (auto i : fitness_v)
		cout << i << "\t";
	cout << "\n";*/
}
template <class C, class D>
void genetic_algorithm<C, D>::mutation(C& circ, const double mutation_prob, default_random_engine& generator)
{
	int idx1, idx2;
	for (int idx = 1; idx < rt_size - 1; idx++) 
	{
		double rn = rand_number(generator);
		if (rn < mutation_prob) 
		{
			uniform_int_distribution<int> randunit(1, rt_size - 2);
			idx1 = randunit(generator);
			do 
			{
				idx2 = randunit(generator);
			} while (idx1 == idx2);

			//Circuit::swap_addresses(circ.route, idx1, idx2);
			swap(circ.route[idx1], circ.route[idx2]);
		}
	}
}
template <class C, class D>
int genetic_algorithm<C, D>::selection(vector<double>& fitness_v, int generation_size, double fitness_total, std::default_random_engine& generator)
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
//template <class C>
//void genetic_algorithm<C>::initialise_circuit_v(vector<C>& gen1, vector<C>& gen2, vector<C>& temp_gen)
//{
//	for (int i = 0; i < lista.generation_size + 1; i++) {
//		gen1[i] = Circuit(obj1.centroids, false);
//		gen2[i] = Circuit(obj1.centroids, true);
//	}
//	for (int i = 0; i < 2; i++)
//		temp_gen[i] = Circuit(obj1.centroids, true);
//}

template <class C, class D>
result genetic_algorithm<C, D>::run_algorithm_genetic(int max_conv_cnt, std::function<double(C&)> fitness_func,
	std::function<void (vector<C>&, vector<C>&, vector<C>&, vector<D>&, int)> initialise_gen_v, std::function<bool(C&)> eval_circ)
{
	//lista.generation_size++;
	default_random_engine generator(lista.seed);
	uniform_int_distribution<int> randgen(0, lista.generation_size - 1);
	vector<C> gen(lista.generation_size + 1), new_gen(lista.generation_size + 1);
	vector<double> fitness_v(lista.generation_size);
	vector<C> temp_v(2);
	result Result;
	int ind1, ind2;
	int gen_cnt = 0, conv_cnt = 0, n, elite_ind;
	double prev_max = -DBL_MAX;
	double fitness_total = 0;

	initialise_gen_v(gen, new_gen, temp_v, obj1.centroids, lista.generation_size); // change this lat one 
	//int max_conv_cnt = max(100, lista.max_generation / 5);
	// reciporcal of fitness remember small distance is better
	double max, min;
	vector<double>::iterator max_it;
	while (gen_cnt <= lista.max_generation) 
	{
		for (int i = 0; i < lista.generation_size; i++)
			fitness_v[i] = fitness_func(gen[i]);
		calc_fitness(max, max_it, min, fitness_total, fitness_v, gen);
		// Store best performing circuit
		elite_ind = std::distance(fitness_v.begin(), max_it);
		new_gen[0] = gen[elite_ind];
#ifdef TEST
		performance_v.push_back(max);
		track_route_ov_g.push_back(gen[elite_ind].route);
#endif

		if (std::abs(max - prev_max) < lista.tolerance)
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
			Result.optimal_performance = max;
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
				uniform_int_distribution<int> randunit(1, rt_size - 2);
				a = randunit(generator);
				while ((b = randunit(generator)) == a);
				crossover_ordered(gen[ind1], gen[ind2], temp_v[0], temp_v[1], a, b);
			}
			else
			{
				temp_v[0] = gen[ind1];
				temp_v[1] = gen[ind2];
			}
			mutation(temp_v[0], lista.mutation_prob, generator);
			mutation(temp_v[1], lista.mutation_prob, generator);
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
#ifdef TEST

	size_t route_gen_size = track_route_ov_g.size();
	size_t perf_v_size = performance_v.size();
	ofstream myfile;
	myfile.open("Routes.txt");
	myfile << "Route size" << " " << "Generations\n";
	myfile << rt_size << " " << perf_v_size << "\n";
	myfile << "X-Coordinate " <<  "Y-Coordinate " << "Route Distance " << "Generation Number\n";
	for (int i = 0 i < perf_v_size; i++)
	{
		for (int j = 0; i < rt_size; j++)
			myfile << track_route_ov_g[i][j].route.x_coord << " " << track_route_ov_g[i][j].route.y_coord << " ";
		myfile << performance_v[i] << " " << i << "\n";
	}
	myfile.close();

#endif
	return Result;
}


