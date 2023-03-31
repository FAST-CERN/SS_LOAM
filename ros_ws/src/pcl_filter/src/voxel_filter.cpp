#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>


int main(int argc, char** argv){
    
    ros::init(argc,argv,"voxel");
    ROS_INFO("Voxel Filtering Node Using PCL!");

    ros::NodeHandle nh;

    return 0;
}
