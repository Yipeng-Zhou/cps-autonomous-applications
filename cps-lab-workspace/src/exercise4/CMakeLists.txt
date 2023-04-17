cmake_minimum_required(VERSION 2.8.3)
project(exercise4)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

generate_messages(DEPENDENCIES std_msgs)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

# IMPORTANT : you must copy and adapt the following lines for each node that you want!

add_executable(emitter src/emitter.cpp)
target_link_libraries(emitter ${catkin_LIBRARIES})
add_dependencies(emitter exercise4_generate_messages_cpp)

add_executable(receiver src/receiver.cpp)
target_link_libraries(receiver ${catkin_LIBRARIES})
add_dependencies(receiver exercise4_generate_messages_cpp)
