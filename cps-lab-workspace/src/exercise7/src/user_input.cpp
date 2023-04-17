#include "ros/ros.h"
#include "std_msgs/Int16.h"

int main(int argc, char **argv) {
        ros::init(argc, argv, "user_input");
        ros::NodeHandle node;
        ros::Publisher pub = node.advertise<std_msgs::Int16>("user_integer", 10);
       	ros::Rate loop_rate(1);
	
	//unsigned int i = 0;
	std_msgs::Int16 msg;
	
        while(ros::ok()) {
		ROS_INFO("Enter number: ");
		scanf("%hd", &msg.data);
		ROS_INFO("%hd", msg.data);
		pub.publish(msg);
		//ros::spinOnce();		
                loop_rate.sleep();
		//i++;
        }

        return 0;
}

