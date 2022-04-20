
#include "ros/ros.h"
#include "std_msgs/String.h"

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("%s",msg->data.c_str());//printing the received message from the publisher in the terminal
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("team_abhiyaan", 1000, chatterCallback);
  ros::spin();
  return 0;
}
