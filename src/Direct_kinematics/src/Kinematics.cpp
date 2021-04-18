#include "ros/ros.h"
#include <tf/tf.h>
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/Pose2D.h"
#include "math.h"


class pub_sub {

public:
  geometry_msgs::TwistStamped speed;
  geometry_msgs::Pose2D position_now;
  geometry_msgs::Pose2D position_old;
  nav_msgs::Odometry position_now_odom;
  double dt;
  bool integration_tipe;

private:
  ros::NodeHandle n; 
  ros::Subscriber sub;
  ros::Publisher pub; 

  
public:
  pub_sub(){
    sub = n.subscribe("/chatter", 1, &pub_sub::callback_m1, this);
    pub = n.advertise<nav_msgs::Odometry>("/rechatter", 1);
  }

  void callback_m1(const nav_msgs::Odometry::ConstPtr& msg){
    
    position_now.x = msg->pose.pose.position.x;
    position_now.y = msg->pose.pose.position.y;
    
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    position_now.theta = yaw;



    if(integration_tipe)
    {
      position_now.x=position_old.x+speed.twist.linear.x*dt*cos(position_now.theta);
      position_now.y=position_old.y+speed.twist.linear.x*dt*sin(position_now.theta);
      position_now.theta=position_old.theta+speed.twist.angular.z*dt;
      position_old=position_now;
    }
    else
    {
      position_now.x=position_old.x+speed.twist.linear.x*dt*cos(position_now.theta+speed.twist.angular.z*dt/2);
      position_now.y=position_old.y+speed.twist.linear.x*dt*sin(position_now.theta+speed.twist.angular.z*dt/2);
      position_now.theta=position_old.theta+speed.twist.angular.z*dt;
      position_old=position_now;
    }

    position_now_odom.pose.pose.position.x=position_now.x;
    position_now_odom.pose.pose.position.y=position_now.y;
    q.setRPY(0,0,position_now.theta);
    q.normalize();
    position_now_odom.pose.pose.orientation.x=q[1];
    position_now_odom.pose.pose.orientation.y=q[2];
    position_now_odom.pose.pose.orientation.z=q[3];
    position_now_odom.pose.pose.orientation.w=q[4];

    pub.publish(position_now_odom);
  }
};

int main(int argc, char **argv) {
  ros::init(argc, argv, "subscribe_and_publish");
  
  pub_sub my_pub_sub;
  
  ros::spin();
  
  return 0;
}
