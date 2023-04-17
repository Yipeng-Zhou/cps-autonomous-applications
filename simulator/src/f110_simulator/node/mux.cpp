#include <ros/ros.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <std_msgs/Char.h>

std_msgs::Char mode_from_k;
ros::Publisher pub;

void callback_r(const ackermann_msgs::AckermannDriveStamped::ConstPtr &drive_st_msg) {
	if(mode_from_k.data == 'r') {
		pub.publish(*drive_st_msg);
	}
}

void callback_f(const ackermann_msgs::AckermannDriveStamped::ConstPtr &drive_st_msg) {
	if(mode_from_k.data == 'f') {
		pub.publish(*drive_st_msg);
	}	
}

void callback_p(const ackermann_msgs::AckermannDriveStamped::ConstPtr &drive_st_msg) {
	if(mode_from_k.data == 'p') {
		pub.publish(*drive_st_msg);
	}	
}

void callback_k(const ackermann_msgs::AckermannDriveStamped::ConstPtr &drive_st_msg) {
	if(mode_from_k.data == 'k') {
		pub.publish(*drive_st_msg);
	}
}

void callback_mode(const std_msgs::Char::ConstPtr &mode) {
	mode_from_k = *mode;
}

void callback_AEB(const ackermann_msgs::AckermannDriveStamped::ConstPtr &drive_st_msg) {
	pub.publish(*drive_st_msg);
	mode_from_k.data = 'k';
}
	

int main(int argc, char *argv[]) {

  	ros::init(argc, argv, "mux");
	ros::NodeHandle node;

        //Set initial mode
	mode_from_k.data = 'k';
	
	ros::Subscriber sub_AEB = node.subscribe("/drive_AEB", 1, callback_AEB);	
	ros::Subscriber sub_mode = node.subscribe("/mode", 1, callback_mode);
	ros::Subscriber sub_r = node.subscribe("/drive_r", 1, callback_r);
	ros::Subscriber sub_f = node.subscribe("/drive_f", 1, callback_f);
	ros::Subscriber sub_p = node.subscribe("/drive_p", 1, callback_p);	
	ros::Subscriber sub_k = node.subscribe("/drive_k", 1, callback_k);	
	pub = node.advertise<ackermann_msgs::AckermannDriveStamped>("/drive", 1);
	
	ros::spin();
	return 0;
}








