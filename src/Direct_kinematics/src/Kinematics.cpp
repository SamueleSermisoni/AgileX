#include "ros/ros.h"
#include <tf/tf.h>
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/TwistStamped.h"
#include "geometry_msgs/Pose2D.h"
#include "math.h"
#include <dynamic_reconfigure/server.h>
#include <agilex/parametersConfig.h>
#include <tf/transform_broadcaster.h>
#include "robotics_hw1/CustomOdom.h"
#include "agilex/set_pose.h"
#include "agilex/reset_pose.h"

class pub_sub {

public:
  geometry_msgs::TwistStamped speed;
  geometry_msgs::Pose2D position_now;
  geometry_msgs::Pose2D position_old;
  nav_msgs::Odometry position_now_odom;
  double dt;
  double time_old;
  bool integration_type;
  int count=0;
  tf::TransformBroadcaster br; 
  robotics_hw1::CustomOdom custom_msg;
  ros::ServiceServer service;
  ros::ServiceServer service1;

private:
  ros::NodeHandle n; 
  ros::Subscriber sub;
  ros::Publisher pub;
  ros::Publisher pub2;
  double x0, y0,theta0;


  dynamic_reconfigure::Server<agilex::parametersConfig> server;
  //boost::shared_ptr<Server> server;
  dynamic_reconfigure::Server<agilex::parametersConfig>::CallbackType f;

  //boost::shared_ptr<F> f;
  
public:
  pub_sub(){
    sub = n.subscribe("velocity_bot", 1, &pub_sub::callback_m1, this);
    pub = n.advertise<nav_msgs::Odometry>("/agilex_odom", 1);
    pub2 = n.advertise<robotics_hw1::CustomOdom>("/custom_odom", 1);
    service = n.advertiseService("set_pose", &pub_sub::set, this);
    service1 = n.advertiseService("reset_pose", &pub_sub::reset, this);


    f = boost::bind(&pub_sub::callback_param, this, _1, _2);
    server.setCallback(f);

    n.getParam("/x0_pose", position_old.x);
    n.getParam("/y0_pose", position_old.y);
    n.getParam("/theta0_pose", position_old.theta);
    

    ROS_INFO("Creato");

  }

  void callback_m1(const geometry_msgs::TwistStamped::ConstPtr& msg){

    
    speed=*msg;

    tf::Quaternion q;
    tf::Quaternion q1;
    //     msg->pose.pose.orientation.x,
    //     msg->pose.pose.orientation.y,
    //     msg->pose.pose.orientation.z,
    //     msg->pose.pose.orientation.w);
    // tf::Matrix3x3 m(q);
    // double roll, pitch, yaw;
    // m.getRPY(roll, pitch, yaw);
    // position_now.theta = yaw;

    dt=speed.header.stamp.toSec()-time_old;
    time_old=speed.header.stamp.toSec();
    
    if(count>1)
    {
        if(!integration_type)
      {
        custom_msg.method.data= "Euler";
        position_now.x=position_old.x+speed.twist.linear.x*dt*cos(position_now.theta);
        position_now.y=position_old.y+speed.twist.linear.x*dt*sin(position_now.theta);
        position_now.theta=position_old.theta+speed.twist.angular.z*dt;
        position_old=position_now;
      }
      else
      {
        custom_msg.method.data= "Runge Kutta";
        position_now.x=position_old.x+speed.twist.linear.x*dt*cos(position_now.theta+speed.twist.angular.z*dt/2);
        position_now.y=position_old.y+speed.twist.linear.x*dt*sin(position_now.theta+speed.twist.angular.z*dt/2);
        position_now.theta=position_old.theta+speed.twist.angular.z*dt;
        position_old=position_now;
      }
       position_now_odom.pose.pose.position.x=position_now.x;
    position_now_odom.pose.pose.position.y=position_now.y;
    q.setRPY(0,0,position_now.theta);
    q1.setRPY(0,0,0);
    q1.normalize();
    position_now_odom.pose.pose.orientation.x=q[0];
    position_now_odom.pose.pose.orientation.y=q[1];
    position_now_odom.pose.pose.orientation.z=q[2];
    position_now_odom.pose.pose.orientation.w=q[3];
    position_now_odom.header.stamp=speed.header.stamp;
    position_now_odom.child_frame_id="robottino";
    position_now_odom.header.frame_id="map";

    pub.publish(position_now_odom);

    tf::Transform transform;
    tf::Transform transform1;

    transform.setOrigin( tf::Vector3(position_now.x, position_now.y, 0) );
    transform.setRotation(q);
    transform1.setRotation(q1);
    br.sendTransform(tf::StampedTransform(transform, speed.header.stamp, "map", "agilex"));
    br.sendTransform(tf::StampedTransform(transform1,speed.header.stamp, "map", "odom"));
    br.sendTransform(tf::StampedTransform(transform1,speed.header.stamp, "map", "world"));
    custom_msg.odom= position_now_odom;
    pub2.publish(custom_msg);


    ROS_INFO("%f", position_now.theta);
    }
    count++;
    

   
  }
  void callback_param(agilex::parametersConfig &config, uint32_t level) {

    integration_type=config.integration_type;

    ROS_INFO("Parameter received %d", integration_type);
  }


  bool set(agilex::set_pose::Request  &req, agilex::set_pose::Response &res)
  {
  position_old.x = req.x;
  position_old.y = req.y;
  position_old.theta = req.theta;

  res.info="Position is set";

  ROS_INFO("New pose is set");
  return true;
  }

  bool reset(agilex::reset_pose::Request  &req, agilex::reset_pose::Response &res)
  {
  position_old.x = 0;
  position_old.y = 0;
  position_old.theta = 0;

  res.info="Position is reset";
  ROS_INFO("New pose is reset");
  return true;
  }

};



int main(int argc, char **argv) {
  ros::init(argc, argv, "Odometry");

  ROS_INFO("NODE STARTED");
  
  pub_sub my_pub_sub;
  
  ros::spin();
  
  return 0;
}
