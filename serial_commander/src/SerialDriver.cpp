#include "SerialDriver.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <thread>


SerialDriver::SerialDriver(std::string port="/dev/ttyACM0", int baudrate=9600): port(port), baudrate(baudrate) {


}

SerialDriver::~SerialDriver(){

}
