#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include <cmath>
#include <ackermann_msgs/AckermannDriveStamped.h>

ros::Publisher pub;
float velocity_nominal = 0.0;
float time_threshold = 0.25;

void callback_velocity(const ackermann_msgs::AckermannDriveStamped::ConstPtr &drive_st_msg) {
	velocity_nominal = drive_st_msg->drive.speed;
}

void callback_scan(const sensor_msgs::LaserScan::ConstPtr& scan) {
	std::vector<float> temp = std::vector<float>(scan->ranges.begin(), scan->ranges.end());

        for(int i = 0; i < 1080; i++) {
        	
		float delta_angle = (i - 540) * scan->angle_increment;
		float velocity_projected = velocity_nominal * cos(delta_angle);
		float TTC = temp[i] / velocity_projected;
		
		if(TTC > 0 && TTC < time_threshold) {
			ROS_INFO("collision direction: %d", i);
			ROS_INFO("TTC: %f", TTC);
			// Make and publish message
    			// Header
    			std_msgs::Header header;
    			header.stamp = ros::Time::now();
    			// Ackermann
    			ackermann_msgs::AckermannDrive drive_msg;
    			drive_msg.speed = 0;
    			drive_msg.steering_angle = 0;
    			// AckermannStamped
    			ackermann_msgs::AckermannDriveStamped drive_st_msg;
    			drive_st_msg.header = header;
    			drive_st_msg.drive = drive_msg;
			// Publish AckermannDriveStamped message to /drive_AEB topic
    			pub.publish(drive_st_msg);

			break;
		}
	}   
}

int main(int argc, char *argv[]) {
	
	ros::init(argc, argv, "AEB");
  	ros::NodeHandle node;
	pub = node.advertise<ackermann_msgs::AckermannDriveStamped>("/drive_AEB", 1);
	ros::Subscriber sub_velocity = node.subscribe("/drive", 1, callback_velocity);
	ros::Subscriber sub_scan = node.subscribe("/scan", 10, callback_scan);
	ros::spin();
	
	return 0;
}
