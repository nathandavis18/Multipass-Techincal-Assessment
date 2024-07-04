#include "ubuntu-parser.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "start parsing" << std::endl;

	UbuntuParser parser("https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json");

	std::cout << parser.getJsonData() << std::endl;
	std::cout << "parser done" << std::endl;
	return 0;
}