#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

struct anemometer_data 
{
    std::vector<geometry_msgs::TwistStamped> msgs;
    int msg_count;
    float msg_freq;

    u_int32_t avg_msg_age;
    bool data_is_fresh;

    float avg_vel;
    float std_dev_vel;

    float avg_azimuth;
    float std_dev_azimuth;

    

};


#endif