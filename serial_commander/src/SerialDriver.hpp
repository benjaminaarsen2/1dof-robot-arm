#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <cstdint>

class SerialDriver {
public:
    SerialDriver(const std::string& port = "/dev/ttyACM0", int baudrate = 9600);
    ~SerialDriver();

    int setAngle(int angle);
    int setTimedAngle(int angle, int time_ms);

private:
    int sendCommand(const std::string& command);

    boost::asio::io_context io;        // use io_context instead of io_service
    boost::asio::serial_port serial;   // must be initialized with io_context

    std::string port_name;
    int baudrate;
};
