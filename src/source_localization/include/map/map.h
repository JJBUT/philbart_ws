#include "nav_msgs/OccupancyGrid.h"

// Include guard
#ifndef MAP_H
#define MAP_H

// Description for a map
typedef struct
{
    nav_msgs::OccupancyGrid map;

    double width, height;

} map_t;

// Load a new map into our map structure
boost::shared_ptr<map_t>  load_map_t(const nav_msgs::OccupancyGrid& map);

#endif
