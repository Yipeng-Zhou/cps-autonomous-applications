#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
#include <cmath>

unsigned int i = 0;
int sum = 0;
ros::Publisher pub;

void callback(const std_msgs::Int16::ConstPtr &msg) {
        i++;
        sum += msg->data;
	std_msgs::Float32 msg2;
        msg2.data = pow(sum, 1/(double)i);
	//ROS_INFO("%f", msg2.data);
        pub.publish(msg2);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "geo_avg");
        ros::NodeHandle node;
	pub = node.advertise<std_msgs::Float32>("geo_result", 10);
        ros::Subscriber sub = node.subscribe("user_integer", 10, callback);
        ros::spin();
        return 0;
}


