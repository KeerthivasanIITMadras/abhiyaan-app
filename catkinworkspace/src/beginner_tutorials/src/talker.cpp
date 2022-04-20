#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("team_abhiyaan", 1000);
  ros::Rate loop_rate(10);
   while (ros::ok())
  {
    std_msgs::String msg;
    std::stringstream ss;
    std::string message="team abhiyaan rocks";
    ss <<message;//passing the message to string stream
    msg.data = ss.str();
    ROS_INFO("%s", msg.data.c_str());
    chatter_pub.publish(msg);//publishing the message
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}