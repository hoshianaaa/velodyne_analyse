#include <ros/ros.h> 
#include "sensor_msgs/PointCloud2.h"
#include <iostream>

int count = 0;

class analyse_data
{
public:
    analyse_data();
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    void pointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg);
};

analyse_data::analyse_data(){
    sub_ = nh_.subscribe("velodyne_points", 1000, &analyse_data::pointsCallback,this);
}

void analyse_data::pointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg){
    std::cout << "header:" << std::endl;
    std::cout << "  frame_id:" << msg->header.frame_id << std::endl;
    std::cout << "height:" << msg->height << std::endl;
    std::cout << "width:" << msg->width << std::endl << std::endl;
    for(int i=0;i<5;i++){
        std::cout << "fields[" << i << "]:" << std::endl;
        std::cout << "  name:" << msg->fields[i].name << std::endl;
        std::cout << "  offset:" << msg->fields[i].offset << std::endl;
        std::cout << "  datatype:" << +msg->fields[i].datatype << std::endl;
        std::cout << "  count:" << msg->fields[i].count << std::endl;
    }
    std::cout << std::endl;

    std::cout << "is_bigendian:" << +msg->is_bigendian << std::endl;
    std::cout << "point_step:" << +msg->point_step << std::endl;
    std::cout << "row_step:" << +msg->row_step << std::endl;
    std::cout << "is_dense:" << +msg->is_dense << std::endl;

    std::cout << "data:" << +msg->data[0]  << std::endl;
    
}

    
int main(int argc, char** argv)
{
    ros::init(argc, argv, "analysis_data");
    analyse_data ana;
    ros::spin();
    return 0;
}
