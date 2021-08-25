#pragma once
#include "drone.h"
#include <numeric>
class rural_drone :
    public drone
{
public:
    rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
        int rotors);
    rural_drone(double payload, double max_flight_time);

    //vritual bool energy_flight_constraint(double L) override;
    std::tuple<int, int, int, int> drone_multi_delivery(int k, int ad_adr, std::vector<std::vector<address_metadata*>>& cl_data, 
        std::vector<address_metadata>& opt_route, double max_payload_cap,
        double max_dist);
    void set_up_single_drone(rural_drone* uav, address_metadata arg, double mass_sum);
    void singular_flight(int k, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route);
    //virtual void set_up_drones(int number_of_drones) override;
    double cost_of_drone; //Currency GBP
    std::vector<rural_drone> drone_v_u_m;
    std::vector<rural_drone> drone_v_u;
    int number_of_drones;
private:
    double x_coord, y_coord;
   	
};

