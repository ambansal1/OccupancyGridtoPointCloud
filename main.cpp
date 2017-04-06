#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "kf_tracker/featureDetection.h"
#include "kf_tracker/CKalmanFilter.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include "opencv2/video/tracking.hpp"
#include <ros/ros.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include "pcl_ros/point_cloud.h"
#include <geometry_msgs/Point.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/Int32MultiArray.h>

#include <sensor_msgs/PointCloud2.h>

#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/geometry.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/common/centroid.h>
 
#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <limits>
#include <utility>
#include <pcl/registration/correspondence_estimation.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <nav_msgs/OccupancyGrid.h>
#include <nav_msgs/GridCells.h>
#include <cv_bridge/cv_bridge.h>

#include <grid_map_ros/GridMapRosConverter.hpp>
#include <pcl/features/boundary.h>
#include <pcl/features/normal_3d.h>

#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <pcl/features/boundary.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/console/time.h>

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;




using namespace std;
using namespace cv;
using namespace grid_map;

//ros::Publisher pub;

ros::Publisher pub;
  void occupancyGridToGridMap(const nav_msgs::OccupancyGrid& input)
{
 sensor_msgs::PointCloud2 pcloud ;

	
	grid_map::GridMap gridMap;

	std::string layer = "1";
	std::vector<std::string> layer1;
	layer1.push_back("1");

	if( grid_map::GridMapRosConverter::fromOccupancyGrid(input ,layer , gridMap ))
		{
		
		};

	sensor_msgs::PointCloud2 cloud_filtered;
	grid_map::GridMapRosConverter::toPointCloud( gridMap, layer1, layer, pcloud);
   



      
		while ( 1)
{
		pub.publish(pcloud);

};
	
	
	

}	


int main(int argc, char** argv)
{
    // ROS init
    ros::init (argc,argv,"PCLOUTPUT");
    ros::NodeHandle nh;
  ros::Subscriber sub1 = nh.subscribe ("map",1,occupancyGridToGridMap);
	
	pub = nh.advertise<sensor_msgs::PointCloud2> ("pcloud", 1);

    ros::spin();


}
