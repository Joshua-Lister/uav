#pragma once
#include "drone.h"
#include <numeric>
#include <algorithm>
class rural_drone :
    public drone
{
public:
    rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
        int rotors);
    rural_drone(double payload, double max_flight_time);

    double cost_of_drone; //Currency GBP
private:
    double x_coord, y_coord;
   	
};

