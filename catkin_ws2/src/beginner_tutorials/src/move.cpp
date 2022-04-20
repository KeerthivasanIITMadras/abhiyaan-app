#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>
#define l 1
float angle1;
float angle2;
float pose1[2];
float pose2[2];
void chatterCallback(const turtlesim::Pose::ConstPtr& msg)
{ 
  angle1=msg->theta;
  pose1[0]=msg->x;
  pose1[1]=msg->y;
  //ROS_INFO("%s",msg->data.c_str());
}
void chatterCallback2(const turtlesim::Pose::ConstPtr& msg)
{
    angle2=msg->theta;
    pose2[0]=msg->x;
    pose2[1]=msg->y;
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "move");
    ros::NodeHandle n;
    ros::Publisher chatter_pub1 = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
    ros::Publisher chatter_pub2 = n.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel", 1000);
    ros::Subscriber sub=n.subscribe<turtlesim::Pose>("/turtle1/pose",1000,chatterCallback);
    ros::Subscriber sub2=n.subscribe<turtlesim::Pose>("/turtle2/pose",1000,chatterCallback2);
    ros::Rate loop_rate(10);
    while (ros::ok())
    {	
    	geometry_msgs::Twist cmd_vel;
        float r=sqrt((pose1[0]-3)*(pose1[0]-3)+(pose1[1]-3)*(pose1[1]-3));
        float w=l/r*r;
        float cosine=cos(angle1);
        float sine=sin(angle1);
        cmd_vel.angular.z=w;
        //cmd_vel.linear.y=cosine*sine*w*(2-5);
        cmd_vel.linear.x=1*cosine*cosine*w+2.5*sine*sine*w;
        //cmd_vel.linear.x=-4*sine*w;
        //cmd_vel.linear.y=2*cosine*w;
        cmd_vel.linear.z=0;
        cmd_vel.angular.x=0;
        cmd_vel.angular.y=0;

        geometry_msgs::Twist cmd_vel2;
        float r2=sqrt(pose2[0]*pose2[0]+pose2[1]*pose2[1]);
        float w2=l/r2*r2;
        float cosine2=cos(angle2);
        float sine2=sin(angle2);
        cmd_vel2.angular.z=w2;
        //cmd_vel2.linear.x=cosine2*sine2*w2*(2+2);
        cmd_vel2.linear.x=1*cosine2*cosine2*w2+2.5*sine2*sine2*w2;
        cmd_vel2.linear.z=0;
        cmd_vel2.angular.x=0;
        cmd_vel2.angular.y=0;

        chatter_pub1.publish(cmd_vel);
        chatter_pub2.publish(cmd_vel2);
        ros::spinOnce();
        loop_rate.sleep();
    }
}
