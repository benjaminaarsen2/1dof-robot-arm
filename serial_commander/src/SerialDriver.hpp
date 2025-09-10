#pragma once

#include <string>



class SerialDriver {
public:
    SerialDriver(std::string port="/dev/ttyACM0", int baudrate=9600);
    ~SerialDriver();

private:
    std::string port;
    int baudrate;

};