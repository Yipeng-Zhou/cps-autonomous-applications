#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <cmath>

unsigned int i = 0;
int sum = 0;

void callback(const std_msgs::Int16::ConstPtr &msg) {
        i++;
        sum += msg->data;
        double avg = pow(sum, 1/(double)i);
        ROS_INFO("avg = %lf", avg);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "geo_avg");
        ros::NodeHandle node;
        ros::Subscriber sub = node.subscribe("user_integer", 10, callback);
        ros::spin();
        return 0;
}


