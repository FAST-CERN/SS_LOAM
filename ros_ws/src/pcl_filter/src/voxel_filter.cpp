#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>

std::string data_root = "/media/fast-cern/EF63BEBDBD3FDB9A/Dataset/Voxel Grid Tutorial";
std::string file_name = "table_scene_lms400.pcd";

int main(int argc, char** argv){
    
    //ROS node init 
    ros::init(argc,argv,"voxel");
    ROS_INFO("Voxel Filtering Node Using PCL!");

    ros::NodeHandle nh;

    //Create PC Variables
    pcl::PCLPointCloud2::Ptr cloud(new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloud_filter(new pcl::PCLPointCloud2());

    //PCD Reader
    pcl::PCDReader reader;
    reader.read(data_root + "/" + file_name, *cloud);
    ROS_INFO("the size of raw point cloud is: %d",cloud->height*cloud->width);

    //Voxel Filter
    pcl::VoxelGrid<pcl::PCLPointCloud2> vox_filter;

    vox_filter.setInputCloud(cloud);
    vox_filter.setLeafSize(0.02f,0.02f,0.02f);
    vox_filter.filter(*cloud_filter);
    ROS_INFO("the size of filtered point cloud is: %d",cloud_filter->height*cloud_filter->width);

    //review the output
    pcl::PCDWriter writer;
    writer.write(data_root+"/vox_filter.pcd",*cloud_filter);
    
    //Visualization
    // pcl::


    return 0;
}
