#include "ros/ros.h"
#include "std_msgs/Int16.h"

int main(int argc, char **argv) {
        ros::init(argc, argv, "emitter");
        ros::NodeHandle node;

        ros::Publisher pub = node.advertise<std_msgs::Int16>("odd", 10);
        ros::Rate loop_rate(1);

        //unsigned int i = 0;
        std_msgs::Int16 msg;

        while(ros::ok()) {
                msg.data = 42;
                ROS_INFO("%hd", msg.data);
                pub.publish(msg);
                //ros::spinOnce();
                loop_rate.sleep();
                //i++;
        }

        return 0;
}

