#include "ubuntu-parser.hpp"
#include <string>
#include <iostream>

/// <summary>
/// Constructor for the UbuntuParser class. Initializes JSON Object with data from the given json file URL
/// </summary>
UbuntuParser::UbuntuParser() : mainObject(loadJsonData("http://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json")) 
{
	getAmd64Products(mainObject);
}

/// <summary>
/// Loops through all amd64 products and sends the versions that are supported to std::cout
/// Is called when the -supported-versions command is used
/// </summary>
void UbuntuParser::displaySupportedVersions()
{
	auto productObjects = mainObject->getObject("products");
	std::cout << "\nCurrent Supported Versions of Ubuntu are:\n";
	for (const auto& x : amd64ProductNames)
	{
		auto currentProduct = productObjects->getObject(x);
		bool isSupported = (currentProduct->get("supported") == "true");
		if (isSupported)
		{
			std::cout << currentProduct->get("release_title").toString() << std::endl;
		}
	}
}

/// <summary>
/// Gets the latest Ubuntu LTS Version from the list of versions and displays to the user.
/// Is called when the -current-version command is used.
/// </summary>
void UbuntuParser::displayCurrentVersion()
{
	auto productObjects = mainObject->getObject("products");
	auto currentReleaseObject = productObjects->getObject(amd64ProductNames.back());
	std::string currentReleaseVersion = currentReleaseObject->get("release_title");
	std::string currentVersionName = currentReleaseObject->get("release_codename");
	std::cout << "\nCurrent Ubuntu Release Version is: " << currentReleaseVersion << ", also known as " << currentVersionName << std::endl;
}

/// <summary>
/// Gets the disk1.img SHA256 of a given Ubuntu Version.
/// Is called when the -disk-image command is used.
/// </summary>
/// <param name="version">The version to check</param>
void UbuntuParser::displayDiskImageSha256(const std::string& version)
{
	auto productObjects = mainObject->getObject("products");
	for (const auto& product : amd64ProductNames)
	{
		auto currentProduct = productObjects->getObject(product);
		if (currentProduct->get("aliases").toString().find(version) != std::string::npos)
		{
			auto currentVersion = currentProduct->getObject("versions")->getObject(currentProduct->getObject("versions")->getNames().back());
			std::string currentVersionTitle = currentProduct->get("release_title").toString();
			for (const auto& item : currentVersion->getObject("items")->getNames())
			{
				if (item == "disk1.img")
				{
					std::string diskImage = currentVersion->getObject("items")->getObject("disk1.img")->get("sha256");
					std::cout << "\nDisk1.img SHA256 of Ubuntu Version " << currentVersionTitle << " is: " << diskImage << std::endl;
					return;
				}
				continue;
			}
		}
	}
	std::cout << "\nNo disk image found for version " << version << std::endl;
	
}

/// <summary>
/// Populates a vector with the names of the amd64 releases.
/// Is called on class initialization.
/// </summary>
/// <param name="objPtr">A pointer to the full JSON object</param>
void UbuntuParser::getAmd64Products(const JsonObject::Ptr objPtr)
{
	auto productObjects = mainObject->getObject("products");
	for (const auto& x : productObjects->getNames())
	{
		if (x.find("amd64") != std::string::npos)
		{
			amd64ProductNames.push_back(x);
		}
	}

}