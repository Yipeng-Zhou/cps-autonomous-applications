#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <vector>

std::vector<int> array;

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
	//for(int k = 0; k < array.size(); k++) {
		//printf("%hd", array[k]);
	//}
	
	//ROS_INFO("half = %d", array.size()/2);
	
	//unsigned n = array.size()/2;
	//ROS_INFO("meadian = %hd", array[n]);	
        ROS_INFO("meadian = %hd", array[array.size()/2]);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "meadian");
        ros::NodeHandle node;
        ros::Subscriber sub = node.subscribe("user_integer", 10, callback);
        ros::spin();
        return 0;
}

