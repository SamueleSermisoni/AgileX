cmake_minimum_required(VERSION 2.8.3)
project(agilex)



find_package(catkin REQUIRED COMPONENTS roscpp dynamic_reconfigure tf geometry_msgs message_generation)

add_service_files(
  FILES
  set_pose.srv
  reset_pose.srv
)

generate_dynamic_reconfigure_options(
  cfg/parameters.cfg
  
)

generate_messages(
DEPENDENCIES
std_msgs
)
catkin_package(CATKIN_DEPENDS message_runtime)


include_directories(include ${catkin_INCLUDE_DIRS})



add_executable(direct_kinematics src/Kinematics.cpp)
add_dependencies(direct_kinematics ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencfg)

target_link_libraries(direct_kinematics ${catkin_LIBRARIES})
