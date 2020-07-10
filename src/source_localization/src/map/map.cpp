#include "../include/map/map.h"

boost::shared_ptr<map_t> load_map_t(const nav_msgs::OccupancyGrid& data)
{
    // Start with a regular pointer then transition to smart pointer for map?
    boost::shared_ptr<map_t> map;

    map->width = 5.0;
    //map->height =
    //map->map =

    return map;
}