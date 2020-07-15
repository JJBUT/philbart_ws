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
add_library(pf src/pf/pf.cpp)
add_library(pf_vector src/pf/pf_vector.cpp)
add_library(pf_pdf src/pf/pf_pdf.cpp)
add_library(sl_sensor src/sensors/sl_sensor.cpp)
add_library(sl_anemometer src/sensors/sl_anemometer.cpp)

target_link_libraries(pf pf_vector pf_pdf)
target_link_libraries(sl_anemometer sl_sensor)
target_link_libraries(source_localization_node map pf pf_vector sl_sensor sl_anemometer)
