#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"

unsigned int i = 0;
float sum = 0;
ros::Publisher pub;

void callback(const std_msgs::Int16::ConstPtr &msg) {
        i++;
        sum += 1 / (float)msg->data;
	std_msgs::Float32 msg3;
        msg3.data = i / sum;
        //ROS_INFO("%f", msg3.data);
        pub.publish(msg3);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "har_avg");
        ros::NodeHandle node;
	pub = node.advertise<std_msgs::Float32>("har_result", 10);
        ros::Subscriber sub = node.subscribe("user_integer", 10, callback);
        ros::spin();
        return 0;
}

