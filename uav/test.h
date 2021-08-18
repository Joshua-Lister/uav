#pragma once
#include "genetic_algorithm.h"
#include "tsp_funcs.h"
#include "driver_code.h"
#include "testclass.h"
bool check_cluster_ids();
bool check_cluster_stopping_condition();
bool check_cluster_ids();
std::tuple<vector<address_metadata>, vector<address_metadata>> setup_adr_v();
bool check_for_duplicate_centroid();
bool GA_optimisation_test_1();
bool GA_optimisation_test_2();
bool check_centroids_distance();
bool mutation_test_1();
bool mutation_test_2();
bool crossover_test();
void run_tests();

