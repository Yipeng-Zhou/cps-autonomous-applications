#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
#include <vector>

std::vector<int> array;
ros::Publisher pub;

void callback(const std_msgs::Int16::ConstPtr &msg) {
        array.push_back(msg->data);
        for(int i = 0; i < array.size(); i++) {
		for(int j = 0; j < array.size() - i; j++) {
			int temp = 0;
			if(array[j] > array[j+1]) {
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}	
	}
	std_msgs::Float32 msg4;
        msg4.data = array[array.size() / 2];
        //ROS_INFO("%f", msg4.data);
        pub.publish(msg4);	
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "meadian");
        ros::NodeHandle node;
	pub = node.advertise<std_msgs::Float32>("meadian_result", 10);
        ros::Subscriber sub = node.subscribe("user_integer", 10, callback);
        ros::spin();
        return 0;
}

