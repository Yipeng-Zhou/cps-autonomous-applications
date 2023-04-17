#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <ctime>

int main(int argc, char **argv) {
        ros::init(argc, argv, "emitter");
        ros::NodeHandle node;

        ros::Publisher pub1 = node.advertise<std_msgs::Bool>("odd", 10);
	ros::Publisher pub2 = node.advertise<std_msgs::Bool>("even", 10);
       	ros::Rate loop_rate(2);

        //unsigned int i = 0;
	unsigned int k = 0;
	std_msgs::Bool msg;
	srand((int) time(0));

        while(ros::ok()) {
		msg.data = true;
		k = rand()%100;
		ROS_INFO("%u", k);
		if(k % 2 != 0) {
			pub1.publish(msg);
		}
		else {
			pub2.publish(msg);
		}
                
		//ros::spinOnce();
                loop_rate.sleep();
                //i++;
        }

        return 0;
}

