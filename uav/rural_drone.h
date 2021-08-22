#pragma once
#include "drone.h"
#include <numeric>
class rural_drone :
    public drone
{
public:
    rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
        int rotors);
    rural_drone();
    ~rural_drone();
    bool energy_flight_constraint(double L) override;
    virtual std::tuple<int, int, int, int> drone_multi_delivery(int k, int ad_adr, vector<vector<address_metadata*>>& cl_data, vector<address_metadata>& opt_route, double max_payload_cap,
        double max_dist) override;
    void set_up_single_drone(rural_drone& uav, address_metadata arg, double mass_sum);
    void singular_flight(int k, vector<vector<address_metadata*>>& cl_data, vector<address_metadata>& opt_route);
    //virtual void set_up_drones(int number_of_drones) override;
    double cost_of_drone; //Currency GBP
    vector<drone> drone_v_u_m;
    vector<drone> drone_v_u;
    int number_of_drones;
private:
    double x_coord, y_coord;
   	
};

