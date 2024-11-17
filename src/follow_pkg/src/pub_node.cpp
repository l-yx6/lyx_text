#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf2_ros/transform_broadcaster.h>

void doodom1(const nav_msgs::Odometry::ConstPtr& msgs){
    static tf2_ros::TransformBroadcaster br;
    geometry_msgs::TransformStamped tfs;
    tfs.header.frame_id ="odom";
    tfs.header.stamp = ros::Time::now();
    tfs.child_frame_id ="tb3_0/base_footprint";
    tfs.transform.translation.x = msgs->pose.pose.position.x;
    tfs.transform.translation.y = msgs->pose.pose.position.y;
    tfs.transform.translation.z = msgs->pose.pose.position.z;
    tfs.transform.rotation = msgs->pose.pose.orientation;
    br.sendTransform(tfs);
}

void doodom2(const nav_msgs::Odometry::ConstPtr& msgs){
    static tf2_ros::TransformBroadcaster br;
    geometry_msgs::TransformStamped tfs;
    tfs.header.frame_id ="odom";
    tfs.header.stamp = ros::Time::now();
    tfs.child_frame_id ="tb3_1/base_footprint";
    tfs.transform.translation.x = msgs->pose.pose.position.x;
    tfs.transform.translation.y = msgs->pose.pose.position.y;
    tfs.transform.translation.z = msgs->pose.pose.position.z;
    tfs.transform.rotation = msgs->pose.pose.orientation;
    br.sendTransform(tfs);
}


int main(int argc, char **argv){
    ros::init(argc, argv, "pub_node");
    ros::NodeHandle n;
    ros::Subscriber sub1=n.subscribe("/tb3_0/odom",100,doodom1);
    ros::Subscriber sub2=n.subscribe("/tb3_1/odom",100,doodom2);
    ros::Rate rate(10);
    ros::spin();
    return 0;
}