cmake_minimum_required(VERSION 2.8.3)
project(filter_syncro)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs geometry_msgs message_filters robotics_hw1)

## Declare a catkin package
catkin_package( CATKIN_DEPENDS geometry_msgs message_filters)

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})


add_executable(syncro src/synchronizer.cpp)
target_link_libraries(syncro ${catkin_LIBRARIES})