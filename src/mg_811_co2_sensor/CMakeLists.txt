cmake_minimum_required(VERSION 2.8.3)
project(mg_811_co2_sensor)

find_package(catkin REQUIRED COMPONENTS 
  roslaunch
  roscpp
  rospy
  std_msgs
  message_generation)

add_message_files(
  FILES
  #AnemometerMsg.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(CATKIN_DEPENDS message_runtime)

roslaunch_add_file_check(launch)

install(DIRECTORY config launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)





