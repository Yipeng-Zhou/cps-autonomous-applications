#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"

unsigned int i = 0;
int sum = 0;
ros::Publisher pub;

void callback(const std_msgs::Int16::ConstPtr &msg) {
        i++;
	sum += msg->data;
	std_msgs::Float32 msg1;
	msg1.data = (float)sum / i;
	//ROS_INFO("%f", msg1.data);
	pub.publish(msg1);	
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "arith_avg");
        ros::NodeHandle node;
	pub = node.advertise<std_msgs::Float32>("arith_result", 10);
        ros::Subscriber sub = node.subscribe("user_integer", 10, callback);
	ros::spin();
        return 0;
}

