#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

void imageCallback(const sensor_msgs::ImageConstPtr &msg)
{
    try
    {
        cv::Mat img = cv_bridge::toCvShare(msg, "bgr8")->image;
        cv::imshow("Webcam Stream", img);
        cv::waitKey(1);
    }
    catch (cv_bridge::Exception &e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "webcam_subscriber");
    ros::NodeHandle nh;

    cv::namedWindow("Webcam Stream");

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("webcam/image", 1, imageCallback);

    ros::spin();

    cv::destroyWindow("Webcam Stream");

    return 0;
}
