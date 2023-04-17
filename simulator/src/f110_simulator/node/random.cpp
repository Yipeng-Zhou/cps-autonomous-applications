#include <ros/ros.h>
#include <ackermann_msgs/AckermannDriveStamped.h>
#include <stdlib.h>

ros::Publisher command_pub;

float mapping[4][2] = {{1.0, 0.0},
                       {1.0, -1.0},
                       {1.0, 1.0},
                       {-1.0, 0.0}
                      };

float speed_limit = 1.0;
float angle_limit = 0.3;

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "random");
  ros::NodeHandle n;
  command_pub = n.advertise<ackermann_msgs::AckermannDriveStamped>("/drive_r", 1);
  ros::Rate loop_rate(2);

  float speed = 0.0;
  float angle = 0.0;

  //unsigned int i = 0;

  while(ros::ok()) {
    unsigned int input = rand()%4;
    speed = mapping[input][0];
    angle = mapping[input][1];

    //Make and publish message
    //Header
    std_msgs::Header header;
    header.stamp = ros::Time::now();
    //Ackermann
    ackermann_msgs::AckermannDrive drive_msg;
    drive_msg.speed = speed * speed_limit;
    drive_msg.steering_angle = angle * angle_limit;
    //AckermannStamped
    ackermann_msgs::AckermannDriveStamped drive_st_msg;
    drive_st_msg.header = header;
    drive_st_msg.drive = drive_msg;
    //publish AckermannDriveStamped message to drive_r topic
    command_pub.publish(drive_st_msg);
    loop_rate.sleep();
    //i++;
  }
  return 0;
}                                                                                                                                                                                 
