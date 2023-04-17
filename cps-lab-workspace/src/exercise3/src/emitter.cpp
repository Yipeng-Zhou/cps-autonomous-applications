#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <ctime>

int main(int argc, char **argv) {
        ros::init(argc, argv, "emitter");
        ros::NodeHandle node;

        ros::Publisher pub = node.advertise<std_msgs::Int16>("odd", 10);
        ros::Rate loop_rate(2);

        //unsigned int i = 0;
        std_msgs::Int16 msg;
	srand((int) time(0));

        while(ros::ok()) {
		msg.data = rand()%100;
                ROS_INFO("%hd", msg.data);
		if(msg.data % 2 != 0) {
			pub.publish(msg);
		}
                //ros::spinOnce();
                loop_rate.sleep();
                //i++;
        }

        return 0;
}

