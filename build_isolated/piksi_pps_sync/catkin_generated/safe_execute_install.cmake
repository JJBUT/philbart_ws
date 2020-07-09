execute_process(COMMAND "/home/jacksubuntu/philbart_ws/build_isolated/piksi_pps_sync/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/jacksubuntu/philbart_ws/build_isolated/piksi_pps_sync/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
