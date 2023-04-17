#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <vector>
#include <cmath>

ros::Publisher pub;

void callback(const sensor_msgs::LaserScan::ConstPtr& scan) {
  	std::vector<float> temp = std::vector<float>(scan->ranges.begin(), scan->ranges.end());

	float max_distance = 0.0;
	float min_distance = 1000000.0;
	int index_max_distance = 0;
	int index_min_distance = 0;
	for(int i = 270; i <= 810; i++) {
		if(temp[i] > max_distance) {
			max_distance = temp[i];
			index_max_distance = i;
		}

		if(temp[i] < min_distance) {
			min_distance = temp[i];
			index_min_distance = i;
		}
	}

	//ROS_INFO("index_max_distance: %d", index_max_distance);
	//ROS_INFO("max_distance: %f", max_distance);
	//ROS_INFO("index_mix_distance: %d", index_min_distance);
	//ROS_INFO("mix_distance: %f", min_distance);
	
	float steering_angle = 0.0;
	float speed = 2.0;


	//Method_1 fail!
	//steering_angle = (index_max_distance - 540) * scan->angle_increment;
	
	//Method_2 fail!
        //if((index_max_distance - 540) < 0) {
        //      steering_angle = -pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
        //}
        //else {
        //     	steering_angle = pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
        //}

	//Method_3 fail!
	//if((index_max_distance - 540) < 0) {
	// 	steering_angle = -pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
	//	if(steering_angle < -0.145) {
	//		steering_angle = -0.145;
	//	}
	//}
	//else {
	//	steering_angle = pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
        //      if(steering_angle > 0.145) {
        //         	steering_angle = 0.145;
        //     	}
	//}

	//Method_4 fail!
	//if(abs(index_max_distance - 540) > 80) {
	//	if((index_max_distance - 540) < 0) {
	//		steering_angle = -pow((abs(index_max_distance - 540) * scan->angle_increment), 4);
	//		if(steering_angle < -0.2) {
	//			steering_angle = -0.2;
	//		}
	//	}
	//	else {
	//		steering_angle = pow((abs(index_max_distance - 540) * scan->angle_increment), 4);
        //     		if(steering_angle > 0.2) {
        //              	steering_angle = 0.2;
        //        	}
	//	}
	//}
	//else {
        //	steering_angle = 0;
        //}

	//Method_5 fail!
	//speed = max_distance / 10 * speed;
	//if(speed > 4) {
	//	speed = 4;
	//}

	//if((index_max_distance - 540) < 0) {
	// 	steering_angle = -pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
	//	if(steering_angle < -0.18) {
	//		steering_angle = -0.18;
	//	}
	//}
	//else {
	//	steering_angle = pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
        //      if(steering_angle > 0.18) {
        //       	steering_angle = 0.18;
        //    	}
	//}
	
	//Method_6 work well!
	//if(min_distance < 0.8) {
	//      steering_angle = -0.5 * (index_min_distance - 540) * scan->angle_increment;
      	//}
	//else {
	//	if((index_max_distance - 540) < 0) {
	// 		steering_angle = -pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
	//		if(steering_angle < -0.18) {
	//			steering_angle = -0.18;
	//		}
	//	}
	//	else {
	//		steering_angle = pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
        //      	if(steering_angle > 0.18) {
        //       		steering_angle = 0.18;
        //   	       	}
	//	}	
	//}

	//Method_7 work well!
	if(abs(index_min_distance - 540) < 250) {
		steering_angle = -0.5 * (index_min_distance - 540) * scan->angle_increment;
	}
	else {
		if((index_max_distance - 540) < 0) {
			steering_angle = -pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
			if(steering_angle < -0.145) {
				steering_angle = -0.145;
			}
		}
		else {
			steering_angle = pow((abs(index_max_distance - 540) * scan->angle_increment), 5);
             		if(steering_angle > 0.145) {
                 		steering_angle = 0.145;
             		}
		}
	}


	
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
	
	ros::init(argc, argv, "gap");
  	ros::NodeHandle node;
	pub = node.advertise<ackermann_msgs::AckermannDriveStamped>("/drive_f", 1);
	ros::Subscriber sub = node.subscribe("/scan", 10, callback);
	ros::spin();
	
	return 0;
}
