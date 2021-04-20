cmake_minimum_required(VERSION 2.8.3)
project(agilex)

#find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS roscpp )

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})



add_executable(direct_kinematics src/Kinematics.cpp)
add_dependencies(direct_kinematics ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

target_link_libraries(direct_kinematics ${catkin_LIBRARIES})
