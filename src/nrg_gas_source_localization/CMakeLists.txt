cmake_minimum_required(VERSION 2.8.3)
project(nrg_gas_source_localization)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(nrg_sl_particle_filter src/nrg_gas_source_localization/nrg_sl_particle_filter.cpp)   #TODO this is the node
target_link_libraries(nrg_sl_particle_filter ${catkin_LIBRARIES})

add_library(nrg_sl_utils src/nrg_gas_source_localization/nrg_sl_utils.cpp)
target_link_libraries(nrg_sl_particle_filter nrg_sl_utils)
