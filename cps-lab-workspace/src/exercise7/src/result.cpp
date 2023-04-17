#include "ros/ros.h"
#include "std_msgs/Float32.h"

float result1 = 0;
float result2 = 0;
float result3 = 0;
float result4 = 0;

void callback1(const std_msgs::Float32::ConstPtr &msg1) {
        result1 = msg1->data;
}

void callback2(const std_msgs::Float32::ConstPtr &msg2) {
        result2 = msg2->data;
}

void callback3(const std_msgs::Float32::ConstPtr &msg3) {
        result3 = msg3->data;
}

void callback4(const std_msgs::Float32::ConstPtr &msg4) {
        result4 = msg4->data;
}


int main(int argc, char **argv) {
        ros::init(argc, argv, "result");
        ros::NodeHandle node;
        ros::Subscriber sub1 = node.subscribe("arith_result", 10, callback1);
	ros::Subscriber sub2 = node.subscribe("geo_result", 10, callback2);
	ros::Subscriber sub3 = node.subscribe("har_result", 10, callback3);
	ros::Subscriber sub4 = node.subscribe("meadian_result", 10, callback4);
	ros::Rate loop_rate(2);

	while(ros::ok()) {
		ROS_INFO("arith_avg = %f", result1);
		ROS_INFO("geo_avg = %f", result2);
		ROS_INFO("har_avg = %f", result3);
		ROS_INFO("meadian = %f\n", result4);
		ros::spinOnce();
		loop_rate.sleep();
	}
        return 0;
}

