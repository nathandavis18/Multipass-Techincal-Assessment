#pragma once
#include "Poco/URIStreamOpener.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"
#include <memory>
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <filesystem>

using Poco::URIStreamOpener;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::Net::HTTPStreamFactory;
using JsonObject = Poco::JSON::Object;

/// <summary>
/// An header-only abstract class that can be used for any JSON Parsing from a given URL
/// </summary>
class MyParser
{
protected:
	/// <summary>
	/// Derived classes can call this function. Loads and returns a JSON Object from a given URL
	/// </summary>
	/// <param name="url">The url of text to download</param>
	/// <returns>A JSON Object of the text data</returns>
	JsonObject::Ptr loadJsonData(const std::string& url)
	{	
		std::string jsonString;
		getUrlResponse(url, jsonString);

		Poco::JSON::Parser parser;
		auto result = parser.parse(jsonString);
		return result.extract<JsonObject::Ptr>();
	}
private:
	/// <summary>
	/// Uses the Poco::Net library
	/// Opens the url to the Ubuntu Cloud Image information and streams it into an istream.
	/// Copies all information into an std::string.
	/// Should not be called by derived/child classes
	/// </summary>
	/// <param name="url">The URL to download from</param>
	/// <param name="outString">A reference to the output string to prevent the need for copying the string</param>
	void getUrlResponse(const std::string& url, std::string& outString)
	{
		HTTPStreamFactory::registerFactory();
		try
		{
			std::filesystem::path filePath = std::filesystem::current_path() / "out.json";
			if (std::filesystem::exists(filePath))
			{
				std::filesystem::remove(filePath);
			}

			{
				std::ofstream outFile("out.json");
				std::unique_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(url));
				Poco::StreamCopier::copyStreamUnbuffered64(*pStr, outFile);
			}
			{
				std::ifstream inputFile("out.json");
				Poco::StreamCopier::copyToString64(inputFile, outString);
			}
			std::filesystem::remove(filePath);
		}
		catch (Exception& ex)
		{
			std::cerr << ex.displayText() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
};