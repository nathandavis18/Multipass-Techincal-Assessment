#include "ubuntu-parser.hpp"
#include <iostream>

/// <summary>
/// Entry point for the application. Determines which command to run based on command line arguments
/// </summary>
/// <param name="argc">Commandline argument count</param>
/// <param name="argv">Commandline arguments</param>
/// <returns></returns>
int main(int argc, char** argv)
{	
	if (argc < 2 || (argc > 2 && (argv[2] != "-d" || argv[2] != "-disk-image")))
	{
		std::cerr << "Invalid Usage. Use [APPNAME] -help to view all possible options";
		exit(EXIT_FAILURE);
	}

	std::string command = argv[1];
	if (command == "-supported-versions" || command == "-s")
	{
		UbuntuParser parser;
		parser.displaySupportedVersions();
	}
	else if (command == "-current-version" || command == "-cv")
	{
		UbuntuParser parser;
		parser.displayCurrentVersion();
	}
	else if (command == "-disk-image" || command == "-d")
	{
		if (argc < 3)
		{
			UbuntuParser parser;
			parser.displayDiskImageSha256("default");
		}
		else if (argc == 3)
		{
			UbuntuParser parser;
			std::string version = argv[2];
			parser.displayDiskImageSha256(version);
		}
	}
	else if (command == "-help" || command == "-h")
	{
		std::string commands = "\nCOMMANDS\n\n-supported-versions {ALIAS: -s}\t\tDisplays all currently supported versions of Ubuntu.\n\n";
		commands += "-current-version {ALIAS: -cv}\t\tDisplays the current LTS version of Ubuntu.\n\n";
		commands += "-disk-image [version] {ALIAS: -d}\tDisplays the SHA256 of the disk1.img of the given version. \n\t\t\t\t\tDefaults to the current version of Ubuntu.\n\n";
		commands += "-help {ALIAS: -h}\t\t\tDisplays this help page\n\n";

		std::cout << commands;
	}
	else
	{
		std::cerr << "\nInvalid command. Use -help for a list of available commands" << std::endl;
		exit(EXIT_FAILURE);
	}
	return 0;
}