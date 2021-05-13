
#include "ros/ros.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "geometry_msgs/PoseStamped.h"
#include "robotics_hw1/MotorSpeed.h"
#include "robotics_hw1/DiffDriveSpeed.h"
#include "nav_msgs/Odometry.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <tf/tf.h>
#include <math.h>
namespace old 
{
double theta_old;
double x_old;
double y_old;
double time_old=4;
 }

void callback(const robotics_hw1::MotorSpeedConstPtr& msg1, 
              const robotics_hw1::MotorSpeedConstPtr& msg2,
              const robotics_hw1::MotorSpeedConstPtr& msg3,
              const robotics_hw1::MotorSpeedConstPtr& msg4,
              /*const nav_msgs::OdometryConstPtr& msg5,*/
              const geometry_msgs::PoseStampedConstPtr& msg6) {
   const double est_gear= 38.20 ;
  
   double dt=msg6->header.stamp.toSec()-old::time_old;
   double vel,omega;

   double x_now=msg6->pose.position.x;
   double y_now=msg6->pose.position.y;

   double v_x= (x_now-old::x_old)/dt;
   double v_y= (y_now-old::y_old)/dt;

   old::x_old=x_now;
   old::y_old=y_now;

   vel=sqrt(v_x*v_x+v_y*v_y);
   double theta2=atan2(v_y,v_x);

   tf::Quaternion q;

   q[0]= msg6->pose.orientation.x;
   q[1]= msg6->pose.orientation.y;
   q[2]= msg6->pose.orientation.z;
   q[3]= msg6->pose.orientation.w;

   double roll, pitch , theta;
  tf::Matrix3x3(q).getRPY(roll, pitch, theta);

  theta=(theta+4);

  double d_theta=(theta)-old::theta_old;

  
  old::theta_old=theta;
  //ROS_INFO("Tempo %f ",old::time_old);
  old::time_old=msg6->header.stamp.toSec();

  omega=d_theta/dt;
 //ROS_INFO("Tempo %f ",theta+4);

 /*  
   ROS_INFO ("Received 4 messages: (%f,%f,%f)", 
     ((msg1->rpm)+(msg3->rpm))*0.000434/2,((msg2->rpm)+(msg4->rpm))*0.000434/2, msg5->twist.twist.angular.z);
   if (((((msg1->rpm)+(msg3->rpm))/2)<0&&(((msg2->rpm)+(msg4->rpm))/2)<0)||((((msg1->rpm)+(msg3->rpm))/2)>0&&(((msg2->rpm)+(msg4->rpm))/2)>0))
   {
     double y0=(((((msg1->rpm)+(msg3->rpm))/2)+(((msg2->rpm)+(msg4->rpm))/2))*3.14*0.1575)/(est_gear*30*msg5->twist.twist.angular.z);
     ROS_INFO ("Estimated Y0: (%f)",y0);
   }

  if (((((msg1->rpm)+(msg3->rpm))/2)<0&&(((msg2->rpm)+(msg4->rpm))/2)>0)||((((msg1->rpm)+(msg3->rpm))/2)>0&&(((msg2->rpm)+(msg4->rpm))/2)<0))
   {
     double gear= ((-msg1->rpm+msg2->rpm-msg3->rpm+msg4->rpm)*3.14*0.1575)/(4*30*msg5->twist.twist.linear.x);
     ROS_INFO ("Estimated gear: (%f)",gear);
   }
   */
  if (dt<0.04 && abs(omega)>0.001)
{
   if (((((msg1->rpm)+(msg3->rpm))/2)<0&&(((msg2->rpm)+(msg4->rpm))/2)<0)||((((msg1->rpm)+(msg3->rpm))/2)>0&&(((msg2->rpm)+(msg4->rpm))/2)>0))
   {
     double y0=(((((msg1->rpm)+(msg3->rpm))/2)+(((msg2->rpm)+(msg4->rpm))/2))*2*3.14*0.1575)/(est_gear*60*omega);

    ROS_INFO ("Received 4 messages: (%f,%f,%f,%f,%f)", 
     ((msg1->rpm)+(msg3->rpm))*0.000434/2,((msg2->rpm)+(msg4->rpm))*0.000434/2,dt ,omega, d_theta);
     ROS_INFO ("Estimated Y0: (%f)",y0);
   }
 }

  /*if (((((msg1->rpm)+(msg3->rpm))/2)<0&&(((msg2->rpm)+(msg4->rpm))/2)>0)||((((msg1->rpm)+(msg3->rpm))/2)>0&&(((msg2->rpm)+(msg4->rpm))/2)<0))
   {
     double gear= ((-msg1->rpm+msg2->rpm-msg3->rpm+msg4->rpm)*3.14*0.1575)/(4*30*vel);
     ROS_INFO ("Estimated gear: (%f)",gear);
   }*/
  
  //pub1.publish(speed);
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "subscriber_sync");

  ros::NodeHandle n;

  ros::Publisher pub1 = n.advertise<robotics_hw1::DiffDriveSpeed>("DiffDrive", 1000);
  message_filters::Subscriber<robotics_hw1::MotorSpeed> sub1(n, "motor_speed_fl", 1);
  message_filters::Subscriber<robotics_hw1::MotorSpeed> sub2(n, "motor_speed_fr", 1);
  message_filters::Subscriber<robotics_hw1::MotorSpeed> sub3(n, "motor_speed_rl", 1);
  message_filters::Subscriber<robotics_hw1::MotorSpeed> sub4(n, "motor_speed_rr", 1);
  /*message_filters::Subscriber<nav_msgs::Odometry> sub5(n, "scout_odom", 1);*/
  message_filters::Subscriber<geometry_msgs::PoseStamped> sub6(n, "gt_pose", 1);

  //typedef message_filters::sync_policies::ExactTime<geometry_msgs::Vector3Stamped, geometry_msgs::Vector3Stamped> MySyncPolicy;
  typedef message_filters::sync_policies
      ::ApproximateTime<robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, /*nav_msgs::Odometry, */ geometry_msgs::PoseStamped> MySyncPolicy;
  
  message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), sub1, sub2, sub3, sub4, /*sub5,*/ sub6);
  sync.registerCallback(boost::bind(&callback, _1, _2, _3, _4, _5/*, _6*/));

  ros::spin();

  return 0;
}
