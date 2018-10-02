// SimpleCore.cpp : Defines the entry point for the console application.
//

#include "SimpleACoreDataServer.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	try
	{
		if (argc == 3) {
			SimpleACoreDataServer server(argv[1],std::atoi(argv[2]),-1);
			server.start();
		}
		else if (argc == 4 ) {
			SimpleACoreDataServer server(argv[1],std::atoi(argv[2]),std::atoi(argv[3]));
			server.start();
		}
		else {
			std::cout << "Usage: SimpleCore <host_ip> <tcp_port_number> <com_port>" << std::endl;
			std::cout << "   Eg. SimpleCore 127.0.0.1 5050 2" << std::endl;
			std::cout << "Or for simulation mode: " << std::endl;
			std::cout << "SimpleCore <host_ip> <tcp_port_number>" << std::endl;
			std::cout << "   Eg. SimpleCore 127.0.0.1 5050" << std::endl;
			return 1;
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught in main(): " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

