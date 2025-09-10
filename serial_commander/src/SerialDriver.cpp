#include "SerialDriver.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <thread>


SerialDriver::SerialDriver(const std::string& _port, int _baudrate): io(),serial(io, _port), port_name(_port),baudrate(_baudrate) {
    serial.set_option(boost::asio::serial_port_base::baud_rate(this->baudrate));
    serial.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
    serial.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
    serial.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
    serial.set_option(boost::asio::serial_port::character_size(8));
}

SerialDriver::~SerialDriver() {
    if (serial.is_open()) {
        serial.close();
    }
}

int SerialDriver::setAngle(int angle){
    std::string command = "turn " + std::to_string(angle);
    return sendCommand(command); //Return a status code to the system
}


int SerialDriver::setTimedAngle(int angle, int time_ms){
    //Disallow if the time / angle is more than 2.5
    if (time_ms / angle < 2.5) {
        std::cerr << "Too fast" << '\n';
        return -1;
    }

    std::string command = "timed_turn " + std::to_string(time_ms) + " " + std::to_string(angle);
    return sendCommand(command); //Return a status code to the system
}


int SerialDriver::sendCommand(const std::string& command) {
    if (!serial.is_open()) {
        std::cerr << "Serial port is not open." << std::endl;
        return -1;
    }

    std::cout << "Sending command: " << command << std::endl;

    boost::asio::streambuf b;
    std::ostream os(&b);
    os << command << "\r";
    boost::asio::write(serial, b.data());
    os.flush();
    return 0;
}