

namespace imu_client_ns
{
    struct data_struct
    {
        int cmd=0x01;
        float x;
        float y;
        float z;
        float ox;
        float oy;
        float oz;
        float ow;
    };


}