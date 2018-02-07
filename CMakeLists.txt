cmake_minimum_required(VERSION 2.8)
project(youbot_autonomus_control)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.40 COMPONENTS date_time thread REQUIRED)

include_directories(
    include
    ${Boost_INCLUDE_DIR}
)

set(SOURCES src/youbot_autonomus_control.cpp)

find_library(ROS_NODE_CONTROL_LIB_FILE ros_node_control_lib)
find_library(KEYBOARD_LIB_FILE keyboard_lib)
find_library(GAMEPAD_LIB_FILE gamepad_lib)

add_executable(youbot_autonomus_control ${SOURCES})
target_link_libraries(youbot_autonomus_control ${ROS_NODE_CONTROL_LIB_FILE} ${KEYBOARD_LIB_FILE} ${GAMEPAD_LIB_FILE} ${Boost_LIBRARIES})

install(TARGETS youbot_autonomus_control DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
