#!/usr/bin/env python

import rospy
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

def camera_publisher():
    rospy.init_node('camera_publisher', anonymous=True)
    pub = rospy.Publisher('image_raw', Image, queue_size=10)
    rate = rospy.Rate(1000)  # 10Hz
    cap = cv2.VideoCapture(0)  # Open default camera

    bridge = CvBridge()

    while not rospy.is_shutdown():
        ret, frame = cap.read()

        if ret:
            # Convert the frame to ROS format
            ros_image = bridge.cv2_to_imgmsg(frame, "bgr8")
            # Publish the image
            pub.publish(ros_image)
        
        rate.sleep()

    # Release the camera when the node is shutdown
    cap.release()

if __name__ == '__main__':
    try:
        camera_publisher()
    except rospy.ROSInterruptException:
        pass
