cmake_minimum_required(VERSION 2.8.3)
project(exercise1)

find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

generate_messages(DEPENDENCIES std_msgs)

catkin_package()

include_directories(include ${catkin_INCLUDE_DIRS})

# IMPORTANT : you must copy and adapt the following lines for each node that you want!

add_executable(Publisher src/Publisher.cpp)
target_link_libraries(Publisher ${catkin_LIBRARIES})
add_dependencies(Publisher exercise1_generate_messages_cpp)

add_executable(Subscriber src/Subscriber.cpp)
target_link_libraries(Subscriber ${catkin_LIBRARIES})
add_dependencies(Subscriber exercise1_generate_messages_cpp)
