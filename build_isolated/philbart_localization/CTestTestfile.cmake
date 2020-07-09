# CMake generated Testfile for 
# Source directory: /home/jacksubuntu/philbart_ws/src/philbart_localization
# Build directory: /home/jacksubuntu/philbart_ws/build_isolated/philbart_localization
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_philbart_localization_roslaunch-check_launch "/home/jacksubuntu/philbart_ws/build_isolated/philbart_localization/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/jacksubuntu/philbart_ws/build_isolated/philbart_localization/test_results/philbart_localization/roslaunch-check_launch.xml" "--return-code" "/home/jacksubuntu/cmake-3.8.0-rc3-Linux-x86_64/bin/cmake -E make_directory /home/jacksubuntu/philbart_ws/build_isolated/philbart_localization/test_results/philbart_localization" "/opt/ros/kinetic/share/roslaunch/cmake/../scripts/roslaunch-check -o '/home/jacksubuntu/philbart_ws/build_isolated/philbart_localization/test_results/philbart_localization/roslaunch-check_launch.xml' '/home/jacksubuntu/philbart_ws/src/philbart_localization/launch' ")
subdirs("gtest")
