#pragma once
#include "genetic_algorithm.h"
#include "tsp_funcs.h"
#include "testclass.h"
#include "intersection.h"
#include <algorithm>

bool check_utility_distance();
bool check_utility_in();
bool check_cluster_stopping_condition();
bool check_cluster_ids();
std::tuple<std::vector<address_metadata>, std::vector<address_metadata>> setup_adr_v();
bool check_for_duplicate_centroid();
bool GA_optimisation_test_1();
bool GA_optimisation_test_2();
bool check_centroids_distance();
bool mutation_test_rsm_1();
bool mutation_test_rsm_2();
bool mutation_test_psm_1();
bool mutation_test_psm_2();
bool mutaiton_test_pm_1();
bool mutaiton_test_pm_1();
bool crossover_test_1();
bool all_adr_visited_multi_drone_test();
bool all_adr_visited_single_drone_test();
void run_tests();
