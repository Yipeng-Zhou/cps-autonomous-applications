cmake_minimum_required(VERSION 2.8.3)
project(exercise6)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

generate_messages(DEPENDENCIES std_msgs)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

# IMPORTANT : you must copy and adapt the following lines for each node that you want!

add_executable(user_input src/user_input.cpp)
target_link_libraries(user_input ${catkin_LIBRARIES})
add_dependencies(user_input exercise6_generate_messages_cpp)

add_executable(arith_avg src/arith_avg.cpp)
target_link_libraries(arith_avg ${catkin_LIBRARIES})
add_dependencies(arith_avg exercise6_generate_messages_cpp)

add_executable(geo_avg src/geo_avg.cpp)
target_link_libraries(geo_avg ${catkin_LIBRARIES})
add_dependencies(geo_avg exercise6_generate_messages_cpp)

add_executable(har_avg src/har_avg.cpp)
target_link_libraries(har_avg ${catkin_LIBRARIES})
add_dependencies(har_avg exercise6_generate_messages_cpp)

add_executable(meadian src/meadian.cpp)
target_link_libraries(meadian ${catkin_LIBRARIES})
add_dependencies(meadian exercise6_generate_messages_cpp)

add_executable(result src/result.cpp)
target_link_libraries(result ${catkin_LIBRARIES})
add_dependencies(result exercise6_generate_messages_cpp)
