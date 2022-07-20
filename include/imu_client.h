#include <stdio.h>
#include <ros/ros.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>
#include "imu_data_struct.h"
#include <geometry_msgs/Pose.h>

#define SERV_PORT 3000


namespace imu_client_ns
{
    class Imu_Client
    {
        public:
        Imu_Client(const char* ip,int port);
        Imu_Client();
        ~Imu_Client();
        int init(const char* ip,int port);
        void update();
        
        geometry_msgs::Pose getdata();

        private:
        struct sockaddr_in server_addr;
        int cfd=0;
        char buf[1024];
        struct data_struct data_struct_;
        geometry_msgs::Pose pose;

    };





}