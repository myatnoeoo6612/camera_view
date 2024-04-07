#include <ros/ros.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "webcam_publisher");
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("webcam/image", 1);

    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        ROS_ERROR("Failed to open camera.");
        return 1;
    }

    cv::Mat frame;
    sensor_msgs::ImagePtr msg;

    ros::Rate rate(30); // Adjust the frame rate as needed

    while (nh.ok())
    {
        cap >> frame;
        if (frame.empty())
        {
            ROS_ERROR("Failed to capture frame.");
            break;
        }

        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub.publish(msg);

        ros::spinOnce();
        rate.sleep();
    }

    cap.release();
    return 0;
}
