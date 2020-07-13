#include "../include/map/map.h"

// Load map into map_t struct; all it really does is calculate the with and height in meters
std::shared_ptr<map_t> load_map_t(const nav_msgs::OccupancyGrid& data)
{
    std::shared_ptr<map_t> map(new map_t());

    // Map width (x-dimension) in meters: m/cell * cell
    map->width = data.info.resolution * data.info.width; 

    // Map height (y-dimension) in meters: m/cell * cell
    map->height = data.info.resolution * data.info.height;

    // Default ROS map format
    map->ros_map = data;

    return map;
}