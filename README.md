# Drone fleet with ROS
This repo intends to run the fleet of drones by Prokura. It will be implemented such that to ensure the following:
- Flight paths don't intersect between the drones
- New connections / process are spawned and killed without affecting the drone operation
- Notification is sent if any drone goes out of connection with master
- Collision avoidance system

## To run the code
- clone and  make sitl for ardupilot from ![here](https://github.com/ArduPilot/ardupilot)
- clone and make install gazebo for ardupilot from ![here](https://github.com/prokuranepal/ardupilot_gazebo), gauthali branch
- install ros and mavros ![here](https://ardupilot.org/dev/docs/ros-install.html#installing-mavros)
- additional setup
```bash
sudo apt-get install python-wstool python-rosinstall-generator python-catkin-tools
```
then, init catkin_ws if u haven't:
```bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
catkin init
```
install mavros
```bash
cd ~/catkin_ws
wstool init ~/catkin_ws/src

rosinstall_generator --upstream mavros | tee /tmp/mavros.rosinstall
rosinstall_generator mavlink | tee -a /tmp/mavros.rosinstall
wstool merge -t src /tmp/mavros.rosinstall
wstool update -t src
rosdep install --from-paths src --ignore-src --rosdistro `echo $ROS_DISTRO` -y

catkin build
sudo ~/catkin_ws/src/mavros/mavros/scripts/install_geographiclib_datasets.sh
```


- clone this repo
```bash
cd ~/catkin_ws/src
git clone <this repo>
catkin build
```



### Launching for circle maker
- each line is run in separate terminal window and in sequence
- launch simulation
```bash
roslaunch pro_fleet multi_drone_sim.launch
```
- run ardupilot controller (FCU)
```bash
roscd pro_fleet scripts
./multi-ardu-iris.sh
```
- connect to fcu with mavros
```bash
roslaunch pro_fleet multi-mav.launch
```
- launch the circle node
```bash
roslaunch pro_fleet multi_square.launch 
```

