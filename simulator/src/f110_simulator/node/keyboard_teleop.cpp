#define _GNU_SOURCE

#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Char.h>
#include <ackermann_msgs/AckermannDriveStamped.h>

ros::Publisher command_pub;
ros::Publisher driving_mode_pub;


float mapping[5][2] = {{1.0, 0.0},
                       {1.0, -1.0},
		       {1.0, 1.0},
		       {-1.0, 0.0},
		       {0.0, 0.0}
                      };

float speed_limit = 1.0;
float angle_limit = 0.3;

char getch() {
        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
        return (buf);
}

//std_msgs::String stdStringToRosString(std::string message) {
//  std_msgs::String msg;
//  msg.data = message;
//  return msg;
//}

//void callback(const sensor_msgs::LaserScan::ConstPtr& scan) {
//  std::vector<float> temp = std::vector<float>(scan->ranges.begin(), scan->ranges.end());
//  copy(ranges, &temp, 1080);
//}

unsigned keyToIndex(char message) {
  unsigned res;

  if (message == 'w') {
    res = 0;
  }
  else if (message == 'd') {
    res = 1;
  }
  else if (message == 'a') {
    res = 2;
  }
  else if (message == 's') {
    res = 3;
  }
  else if (message == ' ') {
    res = 4;
  }
  else {
    res = 0;
  }

  return res;
}

std_msgs::Char keyToMode(char message) {
  std_msgs::Char mode;
  if (message == 'r') {
    mode.data = 'r';
  }
  else if (message == 'f') {
    mode.data = 'f';
  }
  else if (message == 'p') {
    mode.data = 'p';
  }
  else if (message == 'k') {
    mode.data = 'k';
  }
  else {
    mode.data = 'k';
  }
  return mode;
}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "keyboard_teleop");
  ros::NodeHandle node;

  command_pub = node.advertise<ackermann_msgs::AckermannDriveStamped>("/drive_k", 1);
  driving_mode_pub = node.advertise<std_msgs::Char>("/mode", 1);

  float speed = 0.0;
  float angle = 0.0;

  while(ros::ok()) {
    char input  = getch();
    std_msgs::Char mode = keyToMode(input);
    driving_mode_pub.publish(mode);

    if (mode.data == 'k') {
      unsigned index = keyToIndex(input);
      speed = mapping[index][0];
      angle = mapping[index][1]; 

      // Make and publish message
      // Header
      std_msgs::Header header;
      header.stamp = ros::Time::now();
      // Ackermann
      ackermann_msgs::AckermannDrive drive_msg;
      drive_msg.speed = speed * speed_limit;
      drive_msg.steering_angle = angle * angle_limit;
      // AckermannStamped
      ackermann_msgs::AckermannDriveStamped drive_st_msg;
      drive_st_msg.header = header;
      drive_st_msg.drive = drive_msg; 

      // Wait for mux accepting /mode firstly
      //int waiter = 0;
      //while(waiter < (1<<24)) {
      //  waiter++;
      //}
      //
      //if (waiter == (1<<24)) {
      command_pub.publish(drive_st_msg);
      //}
    }
  }
  return 0;
}
