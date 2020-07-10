#include "nav_msgs/OccupancyGrid.h"

// Include guard
#ifndef MAP_H
#define MAP_H

// Description for a map
typedef struct
{
    const nav_msgs::OccupancyGrid map;

    double width, height;

} map_t;

// Load a new map into our map structure
map_t* load_map(const nav_msgs::OccupancyGrid& map);

#endif
