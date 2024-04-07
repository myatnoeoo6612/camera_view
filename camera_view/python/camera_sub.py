#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

def image_callback(data):
    bridge = CvBridge()
    cv_image = bridge.imgmsg_to_cv2(data, "bgr8")
    cv2.imshow("Image Window", cv_image)
    cv2.waitKey(1)

def camera_subscriber():
    rospy.init_node('camera_subscriber', anonymous=True)
    rospy.Subscriber('image_raw', Image, image_callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        camera_subscriber()
    except rospy.ROSInterruptException:
        pass
