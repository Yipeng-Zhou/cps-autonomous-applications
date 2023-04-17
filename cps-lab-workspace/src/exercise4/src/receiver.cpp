#include "ros/ros.h"
#include "std_msgs/Bool.h"

unsigned int i = 0;
unsigned int j = 0;

void callback1(const std_msgs::Bool::ConstPtr &msg) {
        i += 1;
	ROS_INFO("odd: %u; even: %u", i, j);
}

void callback2(const std_msgs::Bool::ConstPtr &msg) {
	j += 1;
	ROS_INFO("odd: %u; even: %u", i, j);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "receiver");
        ros::NodeHandle node;
        ros::Subscriber sub1 = node.subscribe("odd", 10, callback1);
	ros::Subscriber sub2 = node.subscribe("even", 10, callback2);
        ros::spin();
        return 0;
}

