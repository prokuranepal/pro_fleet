#include <util_func.hpp>
//include API
#include <math.h>

int main(int argc, char** argv)
{
    //initialize ros
    ros::init(argc, argv, "main_node");
    ros::NodeHandle main_node("~");

    float radius = 10.0;
    if (!main_node.hasParam("namespace"))
    {

        ROS_INFO("using default namespace");
    } else {
        main_node.getParam("radius", radius);
        ROS_INFO("using radius %f", radius);
    }

    // return 0;
    //initialize control publisher/subscribers
    init_publisher_subscriber(main_node);

    // wait for FCU connection
    wait4connect();

    //wait for used to switch to mode GUIDED
    // wait4start();
    set_mode("GUIDED");

    //create local reference frame
    initialize_local_frame();

    float vert = 5;
    float hor = 20;
    //request takeoff
    takeoff(vert);

    //specify some waypoints
    std::vector<api_waypoint> waypointList;
    api_waypoint nextWayPoint;
    nextWayPoint.x = 0;
    nextWayPoint.y = 0;
    nextWayPoint.z = vert;
    nextWayPoint.psi = 0;
    waypointList.push_back(nextWayPoint);
    nextWayPoint.x = hor;
    nextWayPoint.y = 0;
    nextWayPoint.z = vert;
    nextWayPoint.psi = -90;
    waypointList.push_back(nextWayPoint);
    nextWayPoint.x = hor;
    nextWayPoint.y = hor;
    nextWayPoint.z = vert;
    nextWayPoint.psi = 0;
    waypointList.push_back(nextWayPoint);
    nextWayPoint.x = 0;
    nextWayPoint.y = hor;
    nextWayPoint.z = vert;
    nextWayPoint.psi = 90;
    waypointList.push_back(nextWayPoint);
    nextWayPoint.x = 0;
    nextWayPoint.y = 0;
    nextWayPoint.z = vert;
    nextWayPoint.psi = 180;
    waypointList.push_back(nextWayPoint);
    nextWayPoint.x = 0;
    nextWayPoint.y = 0;
    nextWayPoint.z = vert;
    nextWayPoint.psi = 0;
    waypointList.push_back(nextWayPoint);


    //specify control loop rate. We recommend a low frequency to not over load the FCU with messages. Too many messages will cause the drone to be sluggish
    ros::Rate rate(5.0);
    int counter = 0;
    bool start_circle=false;
    float rad_omega_steps = M_PI/180.0;
    float x = 0.0;
    float y = 0.0;
    float rad_omega = 0.0;
    while(ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
        // if(check_waypoint_reached(.3) == 1)
        // if(!start_circle)
        // {
        // 	ROS_INFO("*********waypoint reached ok");

        // }
        x = radius * sin(rad_omega);
        y = radius * cos(rad_omega);


        // if(check_waypoint_reached(0.5) == 1)
        // {
			ROS_INFO("*********waypoint reached ok");
			// set_destination(100, 100, 30, 0.0);
			set_destination(x, y, vert, 0.0);
			rad_omega += rad_omega_steps;
        // }else{
        // 	//land after all waypoints are reached
        // 	land();
        // }
        // }
    }
    return 0;
}