#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <thread>

int main() {
	std::vector<std::string> strings;
	strings.push_back("Test 1\n");
	strings.push_back("Test 2\n");
	strings.push_back("Hello");
        strings.push_back("Hello world");
        strings.push_back("Hello world!");
        strings.push_back("Hello world!!");
        strings.push_back("Hello world!!!");

       	boost::asio::io_service ioservice;
	boost::asio::serial_port serial(ioservice, "/dev/pts/2");

	serial.set_option(boost::asio::serial_port_base::baud_rate(115200));
	serial.set_option(boost::asio::serial_port::flow_control(boost::asio::serial_port::flow_control::none));
	serial.set_option(boost::asio::serial_port::parity(boost::asio::serial_port::parity::none));
	serial.set_option(boost::asio::serial_port::stop_bits(boost::asio::serial_port::stop_bits::one));
	serial.set_option(boost::asio::serial_port::character_size(boost::asio::serial_port::character_size(8)));

	for (const std::string& s: strings){

	    boost::asio::streambuf b;
	    std::ostream os(&b);
	    os << s << "\r";
	    boost::asio::write(serial, b.data());
	    os.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

     	}

        if (serial.is_open()) {
		serial.close();
	}

	return 0;
}
