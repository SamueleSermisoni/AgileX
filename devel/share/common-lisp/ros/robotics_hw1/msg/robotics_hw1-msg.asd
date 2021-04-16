
(cl:in-package :asdf)

(defsystem "robotics_hw1-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "MotorSpeed" :depends-on ("_package_MotorSpeed"))
    (:file "_package_MotorSpeed" :depends-on ("_package"))
  ))