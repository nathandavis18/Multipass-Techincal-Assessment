#include "ubuntu-parser.hpp"
#include <iostream>
#include <array>


/// <summary>
/// A list of valid commandline arguments. Program exits if invalid command is passed in.
/// </summary>
const std::array<std::string, 8> validCommands = {
		"-supported-versions", "-s",
		"-current-version",    "-cv",
		"-disk-image",         "-d",
		"-help",               "-h"
};

/// <summary>
/// Checks the validity of a given command by looping through the validCommands array.
/// </summary>
/// <param name="command">The command to check for validity</param>
/// <returns>true if valid command, false if not</returns>
bool isValidArgument(const char* command)
{
	for (const auto& x : validCommands)
	{
		if (command == x) return true;
	}
	return false;
}

/// <summary>
/// Entry point for the application. Determines which command to run based on command line arguments
/// </summary>
/// <param name="argc">Commandline argument count</param>
/// <param name="argv">Commandline arguments</param>
/// <returns></returns>
int main(int argc, char** argv)
{	
	if (argc < 2)
	{
		std::cerr << "Invalid Usage. Use UbuntuParser -help to view all possible options" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<std::string> commandLineArgs;
	for (int i = 1; i < argc; ++i)
	{
		if (!isValidArgument(argv[i]))
		{
			std::cerr << "\nUnrecognized command found. Exiting Program\n" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::string currentCommand = argv[i];
		if (currentCommand == "-d" || currentCommand == "-disk-image")
		{
			std::string versionToCheck;
			if (i + 1 < argc)
			{
				std::string temp = argv[i + 1];
				if (temp[0] != '-')
				{
					++i;
					versionToCheck = argv[i];
				}
			}
			else
			{
				versionToCheck = "default";
			}
			commandLineArgs.push_back(currentCommand);
			commandLineArgs.push_back(versionToCheck);
			continue;
		}

		commandLineArgs.push_back(currentCommand);
	}


	//Checking if the help command was used. Cannot use help command with other commands.
	for (const auto& command : commandLineArgs)
	{
		if (command == "-help" || command == "-h")
		{
			std::string commands = "\nCOMMANDS\n\n";
			commands += "-current-version {ALIAS: -cv}\t\tDisplays the current LTS version of Ubuntu.\n\n";
			commands += "-disk-image [version] {ALIAS: -d}\tDisplays the SHA256 of the disk1.img of the given version. \n\t\t\t\t\tDefaults to the current version of Ubuntu.\n\n";
			commands += "-help {ALIAS: -h}\t\t\tDisplays this help page\n\n";
			commands += "-supported-versions {ALIAS: -s}\t\tDisplays all currently supported versions of Ubuntu.\n\n";

			std::cout << commands;
			exit(EXIT_SUCCESS);
		}
	}

	UbuntuParser parser; //Initializes the parser

	for (int i = 0; i < commandLineArgs.size(); ++i)
	{
		const std::string& command = commandLineArgs[i];
		if (command == "-supported-versions" || command == "-s")
		{
			parser.displaySupportedVersions();
		}
		else if (command == "-current-version" || command == "-cv")
		{
			parser.displayCurrentVersion();
		}
		else if (command == "-disk-image" || command == "-d")
		{
			parser.displayDiskImageSha256(commandLineArgs[i + 1]);
		}
	}
	return 0;
}