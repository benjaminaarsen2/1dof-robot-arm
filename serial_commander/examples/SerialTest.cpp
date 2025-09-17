#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "robot_arm_driver/RobotArmDriver.hpp"
#include <boost/thread.hpp>

//Arguments: port, baudrate, angle, time_ms (optional)
#define NUMBER_OF_ARGUMENTS 3

int main(int argc, char const *argv[]){
	if(argc < NUMBER_OF_ARGUMENTS){
		std::cerr << "Please provide a port, baudrate" << '\n';
		return -1;
	}

	int status = 0;
	std::string port = argv[1];
	int baudrate = std::stoi(argv[2]);
	int angle = 0;
	int time_ms = -1;

	//Make a servo controller object
	RobotArmDriver controller(port, baudrate);

	//Wait for user input:
	std::cout << "Enter angle (0-168) and time in ms (optional), or 'exit' to quit:" << '\n';
	while(std::cin >> angle){
		if(std::cin.peek() == '\n'){
			time_ms = -1;
		}else{
			std::cin >> time_ms;
		}
		std::cout << "Setting angle to " << angle << " in " << time_ms << " ms" << '\n';
		if(time_ms < 0){
			status = controller.setAngle(angle);
		}else{
			status = controller.setTimedAngle(angle, time_ms);
		}
		//if the word "exit" is entered, exit the loop
		if(std::cin.peek() == 'e'){
			break;
		}

		if(status != 0){
			std::cerr << "Error setting angle" << '\n';
			break;
		}
	}

	std::cout << "Exited with code: " << status << '\n';
	return status;
}
