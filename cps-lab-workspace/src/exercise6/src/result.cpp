#include "ros/ros.h"
#include "std_msgs/Float32.h"

void callback1(const std_msgs::Float32::ConstPtr &msg1) {
        ROS_INFO("arith_avg = %f", msg1->data);
}

void callback2(const std_msgs::Float32::ConstPtr &msg2) {
        ROS_INFO("geo_avg = %f", msg2->data);
}

void callback3(const std_msgs::Float32::ConstPtr &msg3) {
        ROS_INFO("har_avg = %f", msg3->data);
}

void callback4(const std_msgs::Float32::ConstPtr &msg4) {
        ROS_INFO("meadian = %f", msg4->data);
}


int main(int argc, char **argv) {
        ros::init(argc, argv, "result");
        ros::NodeHandle node;
        ros::Subscriber sub1 = node.subscribe("arith_result", 10, callback1);
	ros::Subscriber sub2 = node.subscribe("geo_result", 10, callback2);
	ros::Subscriber sub3 = node.subscribe("har_result", 10, callback3);
	ros::Subscriber sub4 = node.subscribe("meadian_result", 10, callback4);
        ros::spin();
        return 0;
}

