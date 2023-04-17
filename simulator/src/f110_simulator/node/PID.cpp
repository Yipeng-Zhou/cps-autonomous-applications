#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <vector>
#include <cmath>

ros::Publisher pub;
float current_velocity_nominal = 0.0;
float pre_error = 0.0;
float sum_error = 0.0;

void callback_drive(const ackermann_msgs::AckermannDriveStamped::ConstPtr &drive_st_msg) {
	current_velocity_nominal = drive_st_msg->drive.speed;
}

void callback_scan(const sensor_msgs::LaserScan::ConstPtr& scan) {
	std::vector<float> temp = std::vector<float>(scan->ranges.begin(), scan->ranges.end());
	
	float min_distance_to_rightwall = 1000000.0;
	int index_min_distance_to_rightwall = 0;
	float distance_objective = 1.5;

	for(int i = 0; i <= 540; i++) {
		if(temp[i] < min_distance_to_rightwall) {
			min_distance_to_rightwall = temp[i];
			index_min_distance_to_rightwall = i;
		}
	}
	
	//Calculate anticipated projected distance and error
	float alpha = (540 - index_min_distance_to_rightwall) * scan->angle_increment - 0.5 * M_PI;
	float distance_anticipate = current_velocity_nominal * sin(alpha);
	float error = distance_objective - min_distance_to_rightwall - distance_anticipate;

	//deal with special initial position	
	//if(abs(error) > 1.5) {
	//	error = 1.5;
	//}
	
	float steering_angle = 0.0;
	float speed = 2.0;

	float Kp = 0.45;
	float Kd = 0.20;
	float Ki = 0.10;	
	
	sum_error += error;

	float p_term = Kp * error;
	float d_term = Kd * (pre_error - error);
	float i_term = Ki * sum_error;

	//P control
	steering_angle = p_term;

	//PD control
	//steering_angle = p_term + d_term;

	//PID control
	//steering_angle = p_term + d_term + i_term;
	
	
	//ROS_INFO("min_distance_to_rightwall: %f", min_distance_to_rightwall);
	//ROS_INFO("distance_anticipate: %f", distance_anticipate);
	//ROS_INFO("error: %f", error);
	//ROS_INFO("P Part: %f", p_term);
        //ROS_INFO("D Part: %f", d_term);
        //ROS_INFO("I Part: %f", i_term);
	//ROS_INFO("steering_angle: %f", steering_angle);

	pre_error = error;
	

	// Make and publish message
   	// Header
    	std_msgs::Header header;
   	header.stamp = ros::Time::now();
    	// Ackermann
    	ackermann_msgs::AckermannDrive drive_msg;
    	drive_msg.speed = speed;
    	drive_msg.steering_angle = steering_angle;
    	// AckermannStamped
    	ackermann_msgs::AckermannDriveStamped drive_st_msg;
    	drive_st_msg.header = header;
    	drive_st_msg.drive = drive_msg;
    	// Publish AckermannDriveStamped message to drive topic
    	pub.publish(drive_st_msg);
}

int main(int argc, char *argv[]) {
	
	ros::init(argc, argv, "PID");
  	ros::NodeHandle node;
	pub = node.advertise<ackermann_msgs::AckermannDriveStamped>("/drive_p", 1);
	ros::Subscriber sub_drive = node.subscribe("/drive", 1, callback_drive);
	ros::Subscriber sub_scan = node.subscribe("/scan", 10, callback_scan);
	ros::Rate loop_rate(10);

	while(ros::ok()) {
	ros::spinOnce();
	loop_rate.sleep();
	}

	return 0;
}
