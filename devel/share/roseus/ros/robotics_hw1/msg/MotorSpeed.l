;; Auto-generated. Do not edit!


(when (boundp 'robotics_hw1::MotorSpeed)
  (if (not (find-package "ROBOTICS_HW1"))
    (make-package "ROBOTICS_HW1"))
  (shadow 'MotorSpeed (find-package "ROBOTICS_HW1")))
(unless (find-package "ROBOTICS_HW1::MOTORSPEED")
  (make-package "ROBOTICS_HW1::MOTORSPEED"))

(in-package "ROS")
;;//! \htmlinclude MotorSpeed.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass robotics_hw1::MotorSpeed
  :super ros::object
  :slots (_header _rpm ))

(defmethod robotics_hw1::MotorSpeed
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:rpm __rpm) 0.0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _rpm (float __rpm))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:rpm
   (&optional __rpm)
   (if __rpm (setq _rpm __rpm)) _rpm)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _rpm
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _rpm
       (sys::poke _rpm (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _rpm
     (setq _rpm (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get robotics_hw1::MotorSpeed :md5sum-) "227ff304119c584c2200d7d923efaba9")
(setf (get robotics_hw1::MotorSpeed :datatype-) "robotics_hw1/MotorSpeed")
(setf (get robotics_hw1::MotorSpeed :definition-)
      "Header header
float64 rpm

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :robotics_hw1/MotorSpeed "227ff304119c584c2200d7d923efaba9")


