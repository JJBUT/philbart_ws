cmake_minimum_required(VERSION 2.8.3)
project(source_localization)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(source_localization_node src/source_localization_node.cpp)
target_link_libraries(source_localization_node ${catkin_LIBRARIES})
add_dependencies(source_localization_node source_localization)

add_library(map src/map/map.cpp)
target_link_libraries(source_localization_node map)


add_library(pf_vector src/pf/pf_vector.cpp)
target_link_libraries(source_localization_node pf_vector)

add_library(pf src/pf/pf.cpp)
target_link_libraries(source_localization_node pf)
