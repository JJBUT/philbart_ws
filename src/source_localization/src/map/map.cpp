#include "../include/map/map.h"

boost::shared_ptr<map_t> load_map_t(const nav_msgs::OccupancyGrid& data)
{
    boost::shared_ptr<map_t> map(new map_t());

    map->width = data.info.resolution * data.info.width;
    map->height = data.info.resolution * data.info.height;
    map->ros_map = data;

    return map;
}