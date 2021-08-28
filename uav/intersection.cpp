#include "intersection.h"


intersection::intersection(){}
intersection::~intersection(){}


void intersection::set_parameters(double& elec_cost, double& fuel_cost, double& max_flight_distance, double& max_payload, int& truck_vol_capacity, std::string drone_choice)
{
	fuel_cost = (12 * 1000) / 1000; // Fuel cost per metre (M)
	elec_cost = (0.12 * 1000) / 1000; //Electricy cost per metre (M)
	max_flight_distance = 400; //Metres (M)
	max_payload = 5; //Kilograms (KG)
	truck_vol_capacity = 25;
	drone_choice = "rural";
}

void intersection::set_GA_params_list(GA_param_list& lst)
{
	lst.generation_size = 10;
	lst.max_generation = 100;
	lst.crossover_prob = 0.8;
	lst.mutation_prob = 0.15;
	lst.seed = std::chrono::system_clock::now().time_since_epoch().count();
	lst.tolerance = 1.0e-3;
}
void intersection::run_which_linux()
{

	double elec_cost, max_flight_distance, max_payload, fuel_cost;
	int truck_vol_capacity;
	std::string drone_type;
	set_parameters(elec_cost, fuel_cost, max_flight_distance, max_payload, truck_vol_capacity, drone_type);
	truck t1(truck_vol_capacity);
	GA_param_list GA_list;
	set_GA_params_list(GA_list);
	flight f1(t1, elec_cost, fuel_cost, max_flight_distance, max_payload, drone_type, GA_list);
	
#ifdef TEST

	run_tests();

#elif MULTI
	
	savings multi_save = f1.multi_drone(false);

#elif SINGLE

	savings single_save = f1.single_drone(false);
	
#elif DRONE_COMPARE

	std::vector<savings> compare_d_v;
	compare_d_v = f1.drone_method_savings(f1.max_payload, f1.max_flight_distance);

 #elif ALL_COMPARE
  
  std::vector<double> compare_a_v(3);
  compare_a_v = f1.truck_vs_drone_savings();

#endif

}

void intersection::run_which_windows(std::string choice)
{
	double elec_cost, max_flight_distance, max_payload, fuel_cost;
	int truck_vol_capacity;
	std::string drone_choice;
	set_parameters(elec_cost, fuel_cost, max_flight_distance, max_payload, truck_vol_capacity, drone_choice);
	truck t1(truck_vol_capacity);
	GA_param_list GA_list;
	set_GA_params_list(GA_list);
	flight f1(t1, elec_cost, fuel_cost, max_flight_distance, max_payload, drone_choice, GA_list);

	std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
	
	if (choice == "test")
	{
		run_tests();
	}

	else if (choice == "multi_drone")
	{
		savings multi_save = f1.multi_drone(false);
		std::cout << "Total cost " << "No of Drones " << "No of Trucks ";
		std::cout << multi_save.energy_savings + multi_save.petrol_savings << " " 
			<< multi_save.num_of_drones_savings << " " << multi_save.num_of_trucks_savings;
	}

	else if (choice == "single_drone")
	{
		savings single_save = f1.single_drone(false);
		std::cout << "Total cost " << "No of Drones " << "No of Trucks ";
		std::cout << single_save.energy_savings + single_save.petrol_savings << " "
			<< single_save.num_of_drones_savings << " " << single_save.num_of_trucks_savings;
	}

	else if (choice == "drone_method_compare")
	{
		std::vector<savings> compare_d_v;
		compare_d_v = f1.drone_method_savings(f1.max_payload, f1.max_flight_distance);
		std::cout << "\n";
		std::cout << "       |Total cost |" << "No of Drones |" << "No of Trucks| \n";
		std::cout << "       ---------------------------------------- \n";
		std::cout << "Single |  " << compare_d_v[0].petrol_savings + compare_d_v[0].energy_savings << "  |      " << compare_d_v[0].num_of_drones_savings << "     |    " <<
			compare_d_v[0].num_of_trucks_savings << "       |\n";
		std::cout << "Multi  |  " << compare_d_v[1].petrol_savings + compare_d_v[1].energy_savings << "  |      " << compare_d_v[1].num_of_drones_savings << "     |    " <<
			compare_d_v[1].num_of_trucks_savings << "       |\n";
		std::cout << "       ---------------------------------------- \n";
		std::cout << "\n\n";
		std::cout << "Electricity Savings |" << " Drone Difference  |" << " Truck Difference |\n";
		std::cout << "     " << std::abs(compare_d_v[2].energy_savings) << "        |     " << std::abs(compare_d_v[2].num_of_drones_savings) << "            |     "
			<< "      " << std::abs(compare_d_v[2].num_of_trucks_savings) << "      |\n";
		

	}

	else if (choice == "all_compare")
	{
		std::vector<double> compare_a_v(3);
		compare_a_v = f1.truck_vs_drone_savings();
		std::cout << "       Total cost\n";
		std::cout <<"Truck only" << compare_a_v[0];
		std::cout << "Single " << compare_a_v[1];
		std::cout << "Multi " << compare_a_v[2];

	}
	else
	{
		std::cerr << "Incorrect string passed (WINDOWS OS)\n";
	}


}