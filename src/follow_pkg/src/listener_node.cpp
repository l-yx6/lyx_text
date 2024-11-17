#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/tf.h>
double roll, pitch, yaw;
float x, y, z,w;
int main(int argc, char **argv){
    ros::init(argc, argv, "listen_node");
    ros::NodeHandle n;
    ros::Publisher pub=n.advertise<geometry_msgs::Twist>("tb3_1/cmd_vel", 100);
    geometry_msgs::Twist twist;
    tf2_ros::Buffer tf_buffer(ros::Duration(10.0));
    tf2_ros::TransformListener listener(tf_buffer);
    ros::Rate rate(10);
    while(ros::ok()){
        try{
            geometry_msgs::TransformStamped tfs=tf_buffer.lookupTransform("tb3_1/base_footprint", "tb3_0/base_footprint",ros::Time(0));
            x=tfs.transform.rotation.x;
            y=tfs.transform.rotation.y;
            z=tfs.transform.rotation.z;
            w=tfs.transform.rotation.w;
            tf::Quaternion q(x,y,z,w);
            tf::Matrix3x3(q).getRPY(roll, pitch, yaw);
            if(fabs(tfs.transform.translation.x)+fabs(tfs.transform.translation.y)>=0.5){
              twist.linear.x=0.4*sqrt(pow(tfs.transform.translation.x,2)+pow(tfs.transform.translation.y,2));
              twist.angular.z=4*atan2(tfs.transform.translation.y,tfs.transform.translation.x);
              }
                else {
                    twist.linear.x = 0;
                    twist.linear.y = 0;
                    twist.linear.z = 0;
                    twist.angular.x = 0;
                    twist.angular.y = 0;
                    twist.angular.z = 0;
                }
                pub.publish(twist);
                ros::spinOnce();
                rate.sleep();
            }

            catch(const std::exception &e){
                ROS_INFO("%s",e.what());
            }
        }
    }