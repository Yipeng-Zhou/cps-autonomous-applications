#include "ros/ros.h"
#include "std_msgs/Int16.h"

void callback(const std_msgs::Int16::ConstPtr &msg) {
        ROS_INFO("Recv: %hd", msg->data);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "receiver");
        ros::NodeHandle node;
        ros::Subscriber sub = node.subscribe("odd", 10, callback);
        ros::spin();
        return 0;
}

