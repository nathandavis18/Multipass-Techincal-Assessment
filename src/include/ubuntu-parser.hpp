#pragma once
#include <vector>
#include "myParser.hpp"

/// <summary>
/// The derived class specializing in extracting information from the Ubuntu Cloud Images Json
/// </summary>
class UbuntuParser : public MyParser
{
public:
	UbuntuParser();
	void displaySupportedVersions();
	void displayCurrentVersion();
	void displayDiskImageSha256(const std::string& version);
private:
	void getAmd64Products(const JsonObject::Ptr objPtr);
private:
	std::vector<std::string> amd64ProductNames;
	JsonObject::Ptr mainObject;
};