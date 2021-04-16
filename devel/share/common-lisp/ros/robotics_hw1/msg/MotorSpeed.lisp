; Auto-generated. Do not edit!


(cl:in-package robotics_hw1-msg)


;//! \htmlinclude MotorSpeed.msg.html

(cl:defclass <MotorSpeed> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (rpm
    :reader rpm
    :initarg :rpm
    :type cl:float
    :initform 0.0))
)

(cl:defclass MotorSpeed (<MotorSpeed>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MotorSpeed>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MotorSpeed)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robotics_hw1-msg:<MotorSpeed> is deprecated: use robotics_hw1-msg:MotorSpeed instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MotorSpeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robotics_hw1-msg:header-val is deprecated.  Use robotics_hw1-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'rpm-val :lambda-list '(m))
(cl:defmethod rpm-val ((m <MotorSpeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robotics_hw1-msg:rpm-val is deprecated.  Use robotics_hw1-msg:rpm instead.")
  (rpm m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MotorSpeed>) ostream)
  "Serializes a message object of type '<MotorSpeed>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'rpm))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MotorSpeed>) istream)
  "Deserializes a message object of type '<MotorSpeed>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rpm) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MotorSpeed>)))
  "Returns string type for a message object of type '<MotorSpeed>"
  "robotics_hw1/MotorSpeed")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MotorSpeed)))
  "Returns string type for a message object of type 'MotorSpeed"
  "robotics_hw1/MotorSpeed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MotorSpeed>)))
  "Returns md5sum for a message object of type '<MotorSpeed>"
  "227ff304119c584c2200d7d923efaba9")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MotorSpeed)))
  "Returns md5sum for a message object of type 'MotorSpeed"
  "227ff304119c584c2200d7d923efaba9")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MotorSpeed>)))
  "Returns full string definition for message of type '<MotorSpeed>"
  (cl:format cl:nil "Header header~%float64 rpm~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MotorSpeed)))
  "Returns full string definition for message of type 'MotorSpeed"
  (cl:format cl:nil "Header header~%float64 rpm~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MotorSpeed>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MotorSpeed>))
  "Converts a ROS message object to a list"
  (cl:list 'MotorSpeed
    (cl:cons ':header (header msg))
    (cl:cons ':rpm (rpm msg))
))
