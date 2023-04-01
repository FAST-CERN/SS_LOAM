#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>

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
    
    //PointCloud type trans
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_vis(new pcl::PointCloud<pcl::PointXYZ>());
    pcl::fromPCLPointCloud2(*cloud_filter,*cloud_vis);

    //Visualization
    pcl::visualization::CloudViewer viewer("PointCloud Viewer");
    // visualizer->setBackgroundColor(0,0,0);
    // visualizer->addPointCloud<pcl::PointXYZ>(cloud_vis,"Filtered PointCloud");
    // visualizer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "Filtered PointCloud");
    // visualizer->addCoordinateSystem(5.0);

    viewer.showCloud(cloud_vis);
    while(!viewer.wasStopped()){
    }

    return 0;
}
