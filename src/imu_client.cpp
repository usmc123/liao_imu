#include "imu_client.h"



namespace imu_client_ns
{
    Imu_Client::Imu_Client(const char* ip,int port)
    {
        server_addr.sin_family=AF_INET;
        server_addr.sin_port= htons(port);
        inet_pton(AF_INET,ip,&server_addr.sin_addr.s_addr);
        cfd = socket(AF_INET,SOCK_STREAM,0);
        if(cfd==-1)
        {
            perror("socket error");
            exit(1);
        }
        int ret = connect(cfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
            if(ret==-1)
        {
            perror("connect error");
            exit(1);
        }
    }
    geometry_msgs::Pose Imu_Client::getdata()
    {
        return this->pose;
    }

    void Imu_Client::update()
    {
        const char recmsg[] = "data"; 
        write(cfd,recmsg,sizeof(recmsg));
        int ret=read(cfd,buf,sizeof(buf));
        memcpy((void*)&data_struct_,(void *)buf,sizeof(data_struct_));
        pose.position.x=data_struct_.x;
        pose.position.y=data_struct_.y;
        pose.position.z=data_struct_.z;
        pose.orientation.x=data_struct_.ox;
        pose.orientation.y=data_struct_.oy;
        pose.orientation.z=data_struct_.oz;
        pose.orientation.w=data_struct_.ow;
        if (ret>0)
        {
            ROS_INFO("I have data !!!x=%f,y=%f,z=%f,ox=%f,oy=%f,oz=%f,ow=%f"
            ,pose.position.x
            ,pose.position.y
            ,pose.position.z
            ,pose.orientation.x
            ,pose.orientation.y
            ,pose.orientation.z
            ,pose.orientation.w);
        }
        

    }
    Imu_Client::~Imu_Client()
    {
        const char stopmsg[] = "stop"; 
        write(cfd,stopmsg,sizeof(stopmsg));

    }



}