cmake_minimum_required(VERSION 2.8.3)
project(source_localization)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare a catkin package
catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(source_localization_node src/source_localization_node.cpp)
target_link_libraries(source_localization_node ${catkin_LIBRARIES})
add_dependencies(source_localization_node source_localization)
