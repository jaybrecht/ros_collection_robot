#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include "geometry_msgs/PoseStamped.h"
#include <geometry_msgs/Twist.h>
#include "geometry_msgs/Point.h"
#include "geometry_msgs/Quaternion.h"
#include <sensor_msgs/Image.h>
#include "sensor_msgs/LaserScan.h"
#include "sensor_msgs/LaserEcho.h"
#include "nav_msgs/Odometry.h"
#include "ros/ros.h"
#include <ros/package.h>
#include <yaml-cpp/yaml.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include "../include/path_planner.h"
#include "../include/order_manager.h"
#include "../include/node.h"
#include "../include/decoder.h"
#include "../include/line.h"
#include "../include/polygon.h"
#include <ros_collection_robot/Cube.h>

class Navigator{

private:
    bool found_object_;
    int object_detector_count;
    double lidar_min_front_;
    PathPlanner path_planner_;
    geometry_msgs::Point cube_position_;
    ros::NodeHandle nh_;
    ros::Subscriber lidar_sub_;
    ros::Subscriber odom_sub_;
    ros::Publisher vel_pub_;
    ros::Publisher collector_pub_;
    geometry_msgs::Point robot_location_;
    double robot_rotation_; // rotation about z in radians (0 - 2pi)
    tf::Transform transform_;
    tf::TransformBroadcaster br_;
    std::vector<char> cubes_;
    PathPlanner planner;
    Decoder decoder;

public:
    bool determined_pose;
    bool cube_detected_;
    bool approaching_cube_;
    int current_waypoint_;
    std::vector<char> order_;
    std::vector<geometry_msgs::Point> waypoints;
    Navigator();
    void lidarCallback(const sensor_msgs::LaserScan::ConstPtr&);
    void odomCallback(const nav_msgs::Odometry::ConstPtr&);
    void parseWaypoints(std::string);
    void facePoint(geometry_msgs::Point);
    int driveToPoint(geometry_msgs::Point);
    void stop();
    void reverse(double);
    void checkCollectionObject(std::vector<double>);
    bool navigate();
    void goToCollectionObject();
    void driveToDropOff();
};
