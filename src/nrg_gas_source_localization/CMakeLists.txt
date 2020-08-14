cmake_minimum_required(VERSION 2.8.3)
project(nrg_gas_source_localization)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg gmx200_anemometer mg_811_co2_sensor message_filters tf2_ros)


## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(nrg_sl_node src/nrg_sl_node.cpp)  
target_link_libraries(nrg_sl_node nrg_sl_particle_filter nrg_sl_utils ${catkin_LIBRARIES})

add_library(nrg_sl_utils src/nrg_gas_source_localization/nrg_sl_utils.cpp)
add_library(nrg_sl_particle_filter src/nrg_gas_source_localization/nrg_sl_particle_filter.cpp)


add_executable(nrg_sl_data_test_node src/nrg_sl_data_test_node.cpp)  
target_link_libraries(nrg_sl_data_test_node nrg_sl_utils ${catkin_LIBRARIES})
