#pragma once
#include "drone.h"
#include <numeric>
class rural_drone :
    public drone
{
public:
    rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
        int rotors);
    ~rural_drone();
    /*rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
        int rotors);*/
  /*  double power_consumption() override;
    double time_to_charge() override;
    void set_h_velocity_drone(double m_h_v) override;
    void set_v_velocity_drone(double m_v_v) override;
    void set_battery_time() override;
    void set_payload_capacity() override;*/
    bool energy_flight_constraint(double L) override;
    virtual std::tuple<int, int, int, int> drone_delivery(int k, int ad_adr, vector<vector<address_metadata*>>& cl_data, vector<address_metadata>& opt_route, double max_payload_cap,
        double max_dist) override;
    virtual void set_up_drones(int number_of_drones) override;
    double cost_of_drone; //Currency GBP
    vector<drone*> drone_v_u;
    int number_of_drones;
private:
    double x_coord, y_coord;
   	
};

