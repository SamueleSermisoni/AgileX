
#include "ros/ros.h"
#include "geometry_msgs/Vector3Stamped.h"
#include "robotics_hw1/MotorSpeed.h"
#include "robotics_hw1/DiffDriveSpeed.h"
#include "nav_msgs/Odometry.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/sync_policies/approximate_time.h>


void callback(const robotics_hw1::MotorSpeedConstPtr& msg1, 
              const robotics_hw1::MotorSpeedConstPtr& msg2,
              const robotics_hw1::MotorSpeedConstPtr& msg3,
              const robotics_hw1::MotorSpeedConstPtr& msg4,
              const nav_msgs::OdometryConstPtr& msg5) {
   const double est_gear= 38.20 ;

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
  message_filters::Subscriber<nav_msgs::Odometry> sub5(n, "scout_odom", 1);
   

  //typedef message_filters::sync_policies::ExactTime<geometry_msgs::Vector3Stamped, geometry_msgs::Vector3Stamped> MySyncPolicy;
  typedef message_filters::sync_policies
      ::ApproximateTime<robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, robotics_hw1::MotorSpeed, nav_msgs::Odometry> MySyncPolicy;
  
  message_filters::Synchronizer<MySyncPolicy> sync(MySyncPolicy(10), sub1, sub2, sub3, sub4, sub5);
  sync.registerCallback(boost::bind(&callback, _1, _2, _3, _4, _5));

  ros::spin();

  return 0;
}
