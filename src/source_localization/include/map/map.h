#include "nav_msgs/OccupancyGrid.h"

// Include guard
#ifndef MAP_H
#define MAP_H

// Structure used to store maps for the pf
typedef struct
{
    // Original ROS map
    nav_msgs::OccupancyGrid ros_map;

    //Calculated dimensions in meters
    double width, height;

} map_t;

// Load a new map into our map structure
boost::shared_ptr<map_t>  load_map_t(const nav_msgs::OccupancyGrid& map);

#endif
