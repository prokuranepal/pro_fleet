#include <util_func.hpp>
//include API 


int main(int argc, char** argv)
{
	//initialize ros 
	ros::init(argc, argv, "main_node");
	ros::NodeHandle main_node("~");
	
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
	float hor = 5;
	//request takeoff
	takeoff(vert);
	// set_mode("CIRCLE");

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
	ros::Rate rate(2.0);
	int counter = 0;
	while(ros::ok())
	{
		ros::spinOnce();
		rate.sleep();
		// if(check_waypoint_reached(.3) == 1)
		if(check_waypoint_reached(0.5) == 1)
		{
			ROS_INFO("*********waypoint reached ok");
			if (counter < waypointList.size())
			{
				set_destination(waypointList[counter].x,waypointList[counter].y,waypointList[counter].z, waypointList[counter].psi);
				counter++;
			}else{
				//land after all waypoints are reached
				land();
			}
		}
	}
	return 0;
}