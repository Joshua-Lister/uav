#pragma once
#include "drone.h"
class urban_drone :
    public drone
{
public:
    urban_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
        int rotors);
    double max_flight_time = -1;
    //virtual bool energy_flight_constraint(double L);
    double cost_of_drone; //Currency GBP
private:
    double x_coord, y_coord;
};

