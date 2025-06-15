# OpenRTM_aist_mosquitto_mqtt_interface

This software is a set of **MQTT (Message Queuing Telemetry Transport)** communication interface extension modules for OpenRTM-aist C++ developed by AIST, Japan.

OpenRTM-aist is a reference implementation of RT-Middleware, one of the robotics middleware. This software allows you to extend the MQTT communication interface to the components of a robotic system on RT-Middleware, thus enabling you to build a seamless IoRT (Internet of Robotic Things) system within the framework of RT-Middleware.

Normally, an MQTT bridge is required for IoRT systemization of robot systems using ROS1 or ROS2, the de facto standard for robotics middleware. However, in IoRT systemization of robotic systems using RT-Middleware, a bridge is not necessary because the communication interface is embedded in the components that make up the system.

This eliminates the need for extra inter-process communication due to the introduction of bridges, and thus contributes to the communication performance of the entire IoRT system.

## Requirement

To install and use the MQTT communication modules, you will need the C++ version of OpenRTM-aist and the mosquitto MQTT client library.

* OpenRTM-aist-C++ ver. 2.0.x 
* libmosquittopp

In addition, an MQTT broker (server) is required for actual MQTT communication in a robot system on RT-Middleware. These communication module have been tested with Eclipse Mosquitto MQTT broker of OSS.

## Installation

The following assumes installation on each Linux distribution, Ubuntu or debian.

### How to install MQTT communication modules to OpenRTM-aist-C++ ver. 2.0.x

(1) For details on how to install OpenRTM-aist-C++, please refer to the official OpenRTM-aist website of the National Institute of Advanced Industrial Science and Technology (AIST). We omit it here.

(2) Install the mosquitto MQTT client library.
```bash
sudo apt install libmosquittopp-dev
```

(3) Clone the files related to MQTT communication modules from this site and install the MQTT communication modules.
```bash
$ cd ~/
$ git clone https://github.com/dyubicuoa/OpenRTM_aist_mosquitto_mqtt_interface
$ cd OpenRTM_aist_mosquitto_mqtt_interface
$ mkdir build
$ cd build
$ cmake ..
$ make
```

This will create **OutPortMosquittoPublisher.so**, an MQTT transmitter module, and **InPortMosquittoSubscriber.so**, an MQTT receiver module, under `~/OpenRTM_aist_mqttcpp_interface/build/lib`. You can also copy it under `/usr/local/lib` with the command "sudo make install".

(4) Install one of the MQTT brokers if necessary. The Mosquitto MQTT broker can be installed as follows.
```bash
sudo apt install mosquitto
```
