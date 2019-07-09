#include <ros/ros.h> 
#include "sensor_msgs/PointCloud2.h"
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>

int count = 0;

class get_one_ring
{
public:
    get_one_ring();
private:
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    ros::Publisher pub_;
    void pointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg);
};

get_one_ring::get_one_ring(){
    sub_ = nh_.subscribe("velodyne_points", 1000, &get_one_ring::pointsCallback,this);
    pub_ = nh_.advertise<sensor_msgs::PointCloud2>("one_ring", 2, true);
}

void get_one_ring::pointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg){

    
    pcl::PointCloud<pcl::PointXYZ> cloud_pcl;
    cloud_pcl.width = msg->height * msg->width / 8;
    cloud_pcl.height = 1;
    cloud_pcl.points.resize(cloud_pcl.width * cloud_pcl.height);
    int counter = 0;
 
    for (uint j=0; j < msg->height * msg->width; j++){
        int arrayPosX = j * msg->point_step + msg->fields[0].offset;
        int arrayPosY = j * msg->point_step + msg->fields[1].offset;
        int arrayPosZ = j * msg->point_step + msg->fields[2].offset;
        int ring = msg->data[j * msg->point_step + msg->fields[4].offset];
        std::cout << "ring:" << ring << " counter:" << counter << std::endl;


    // compute position in array where x,y,z data start
    float x;
    float y;
    float z;

    memcpy(&x, &msg->data[arrayPosX], sizeof(float));
    memcpy(&y, &msg->data[arrayPosY], sizeof(float));
    memcpy(&z, &msg->data[arrayPosZ], sizeof(float)); 
   
    std::cout << "x:" << x << " y:" << y << " z:" << z ;
    std::cout << " msg->point_step:" << msg->point_step << std::endl;

        

        if(ring == 15){
            cloud_pcl.points[counter].x = x;
            cloud_pcl.points[counter].y = y;
            cloud_pcl.points[counter].z = z;
            counter++;
        }
    }

    sensor_msgs::PointCloud2 ring;
    pcl::toROSMsg(cloud_pcl, ring);
    ring.header.frame_id = "velodyne";
    pub_.publish(ring);
}

    
int main(int argc, char** argv)
{
    ros::init(argc, argv, "one_ring");
    get_one_ring x;
    ros::spin();
    return 0;
}
