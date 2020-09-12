#!/bin/bash

gnome-terminal --tab -- bash -c "sim_vehicle.py -v ArduCopter -f gazebo-drone1 -I0 -m --mav10 --out=tcpin:0.0.0.0:8000 " 
gnome-terminal --tab -- bash -c "sim_vehicle.py -v ArduCopter -f gazebo-drone2 -I1 -m --mav10 --out=tcpin:0.0.0.0:8100 " 
gnome-terminal --tab -- bash -c "sim_vehicle.py -v ArduCopter -f gazebo-drone3 -I2 -m --mav10 --out=tcpin:0.0.0.0:8200 " 
# gnome-terminal --tab -- bash -c "sim_vehicle.py -v ArduPlane -f gazebo-drone4 -I3 --out=tcpin:0.0.0.0:8300 " 

