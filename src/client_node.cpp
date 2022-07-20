#include "imu_client.h"
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>



int main(int argc, char * argv[])
{

    setlocale(LC_ALL,"");
    ros::init(argc, argv, "imu_client");
    ros::NodeHandle nh;
    imu_client_ns::Imu_Client imu_client_("192.168.1.10",6000);


    ros::Publisher pub = nh.advertise<geometry_msgs::Pose>("/imu_pub",1);

    ros::Rate rate(125);
    while (ros::ok())
    {
        imu_client_.update();
        pub.publish(imu_client_.getdata());
        rate.sleep();
    }
    ros::shutdown();
    return 0;
    
}
