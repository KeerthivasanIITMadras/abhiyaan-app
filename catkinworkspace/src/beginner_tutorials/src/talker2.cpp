#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include <bits/stdc++.h>
#include <vector>

std_msgs::String message;

std::string stringreverse(std::string line)
{
    std::vector <std::string> tokens;
    std::stringstream v(line);
    std::string intermediate;
    while(getline(v,intermediate,' '))
    {
        tokens.push_back(intermediate);
    }
    std::string k="";
    for(int i=0;i<tokens.size();i++)
    {   
      
        std::string t=tokens[i];
        reverse(t.begin(),t.end());
        k+=t+" ";
    }
    return k;
}
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{ 
  std::string line=msg->data;
  std::string revline=stringreverse(line);
  message.data=revline;
  ROS_INFO("%s",message.data.c_str());
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker2");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("team_abhiyaan", 1000, chatterCallback);
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("naayibha_maet", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std_msgs::String msg2;
    std::stringstream ss;
    ss<<message.data;
    msg2.data = ss.str();
    ROS_INFO("%s",message.data.c_str());
    chatter_pub.publish(message);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}