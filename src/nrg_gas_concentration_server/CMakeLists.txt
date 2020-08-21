cmake_minimum_required(VERSION 3.0.2)
project(nrg_gas_concentration_server)

add_compile_options(-std=c++11 -g)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  std_msgs
  message_generation
  rostest
)

################################################
## Declare ROS messages, services and actions ##
################################################

 add_message_files(
  FILES
  GasSource.msg
  WindParams.msg
)

add_service_files(
  FILES
  GetConcentration.srv
  SetSource.srv
  SetWindParams.srv
)

generate_messages(
  DEPENDENCIES
  geometry_msgs
  std_msgs
)


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES nrg_gas_concentration_server
#  CATKIN_DEPENDS geometry_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/${PROJECT_NAME}/nrg_gas_concentration_server.cpp
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME}_node src/nrg_gas_concentration_server_node.cpp)

## Rename C++ executable without prefix
## The above recommended prefix causes long target names, the following renames the
## target back to the shorter version for ease of user use
## e.g. "rosrun someones_pkg node" instead of "rosrun someones_pkg someones_pkg_node"
# set_target_properties(${PROJECT_NAME}_node PROPERTIES OUTPUT_NAME node PREFIX "")

## Add cmake target dependencies of the executable
## same as for the library above
# add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_node
  ${catkin_LIBRARIES}
  nrg_gas_concentration_server
)


#############
## Testing ##
#############

if(CATKIN_ENABLE_TESTING)
  add_rostest_gtest(test_nrg_gas_concentration_server
                    test/test_nrg_gas_concentration_server.test
                    test/test_nrg_gas_concentration_server.cpp)
  target_link_libraries(test_nrg_gas_concentration_server nrg_gas_concentration_server ${catkin_LIBRARIES} ${rostest_LIBRARIES})
endif()

