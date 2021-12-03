#include <ros/ros.h>
#include <iostream>
#include <string>
#include <tf/transform_broadcaster.h>

#include <tf_conversions/tf_eigen.h>
#include <tf/transform_listener.h>


using namespace std;

tf::Transform worldTbase_link;
tf::Transform base_linkTee_link;

void print4x4Matrix(const Eigen::Matrix4d & matrix)
{
    printf("Rotation matrix :\n");
    printf("    | %6.3f %6.3f %6.3f | \n", matrix(0, 0), matrix(0, 1), matrix(0, 2));
    printf("R = | %6.3f %6.3f %6.3f | \n", matrix (1, 0), matrix (1, 1), matrix (1, 2));
    printf("    | %6.3f %6.3f %6.3f | \n", matrix (2, 0), matrix (2, 1), matrix (2, 2));
    printf("Translation vector :\n");
    printf("t = < %6.3f, %6.3f, %6.3f >\n\n", matrix (0, 3), matrix (1, 3), matrix (2, 3));
}


void tcp_callback(const geometry_msgs::Twist& pose)
{
            // tf::Matrix3x3 transm_r;
            // transm_r.setValue(eigen_camera2object(0, 0), eigen_camera2object(0, 1), eigen_camera2object(0, 2),
            //                   eigen_camera2object(1, 0), eigen_camera2object(1, 1), eigen_camera2object(1, 2),
            //                   eigen_camera2object(2, 0), eigen_camera2object(2, 1), eigen_camera2object(2, 2));
            // tf::Quaternion q;
            // transm_r.getRotation(q);
            // transform.setOrigin(tf::Vector3(eigen_camera2object(0, 3), eigen_camera2object(1, 3), eigen_camera2object(2, 3)));
            // transform.setRotation(q);

            //tf::Transform gripper2object = gripper2camera*camera2object;



base_linkTee_link.setOrigin(tf::Vector3(pose.linear.x, pose.linear.y, pose.linear.z));
tf::Quaternion q;
q.setRPY(pose.angular.x, pose.angular.y, pose.angular.z);
base_linkTee_link.setRotation(q);

}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "pub_base_and_ee_link");
    ros::NodeHandle node;

    ros::Subscriber scene_sub = node.subscribe("/robot_driver/tool_point",10, tcp_callback);

    ros::Rate loop_rate(50);

worldTbase_link.setIdentity();
base_linkTee_link.setIdentity();

    ros::Duration(3).sleep(); // wait for camera msg

    //    Eigen::Matrix4d trans_inverse;
    Eigen::Matrix4d eigen_camera2object;


    /******  transform br_worldTbase_linkoadcaster  ******/
    static tf::TransformBroadcaster br_worldTbase_link;
    static tf::TransformBroadcaster br_base_linkTee_link;


    while(ros::ok())
    {
            ros::spinOnce();




            // tf::Matrix3x3 transm_r;
            // transm_r.setValue(eigen_camera2object(0, 0), eigen_camera2object(0, 1), eigen_camera2object(0, 2),
            //                   eigen_camera2object(1, 0), eigen_camera2object(1, 1), eigen_camera2object(1, 2),
            //                   eigen_camera2object(2, 0), eigen_camera2object(2, 1), eigen_camera2object(2, 2));
            // tf::Quaternion q;
            // transm_r.getRotation(q);
            // transform.setOrigin(tf::Vector3(eigen_camera2object(0, 3), eigen_camera2object(1, 3), eigen_camera2object(2, 3)));
            // transform.setRotation(q);

            //tf::Transform gripper2object = gripper2camera*camera2object;



            br_worldTbase_link.sendTransform(tf::StampedTransform(worldTbase_link, ros::Time::now(), "world", "base_link"));
br_base_linkTee_link.sendTransform(tf::StampedTransform(base_linkTee_link, ros::Time::now(), "base_link", "ee_link"));
            loop_rate.sleep();
        }

        return(0);
    }
