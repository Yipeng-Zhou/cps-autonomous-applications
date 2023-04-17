#include "ros/ros.h"
#include "std_msgs/Int16.h"

unsigned int i = 0;
float sum = 0;

void callback(const std_msgs::Int16::ConstPtr &msg) {
        i++;
        sum += 1 / (float)msg->data;
        float avg = i / sum;
        ROS_INFO("avg = %f", avg);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "har_avg");
        ros::NodeHandle node;
        ros::Subscriber sub = node.subscribe("user_integer", 10, callback);
        ros::spin();
        return 0;
}

