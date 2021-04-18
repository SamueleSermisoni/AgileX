cmake_minimum_required(VERSION 2.8.3)
project(direct_kinematics)

#find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
)

catkin_package()

include_directories(
  include ${catkin_INCLUDE_DIRS}
)



add_executable(Odometry_calculator
  src/Kinematics.cpp
)
add_dependencies(Odometry_calculator 
	${${PROJECT_NAME}_EXPORTED_TARGETS} 
	${catkin_EXPORTED_TARGETS})
target_link_libraries(Odometry_calculator
  ${catkin_LIBRARIES}
)
