#pragma once
#include "Poco/URIStreamOpener.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"
#include <memory>
#include <string>
#include <algorithm>
#include <sstream>

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
	/// Opens the url and streams the data into a string to later be parsed by the JSON library.
	/// </summary>
	/// <param name="url">The URL to open</param>
	/// <param name="outString">The output string to prevent unnecessary copies</param>
	void getUrlResponse(const std::string& url, std::string& outString)
	{
		HTTPStreamFactory::registerFactory();
		try
		{
			std::unique_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(url));
			Poco::StreamCopier::copyToString64(*pStr, outString, 16384);
		}
		catch (Exception& ex)
		{
			std::cerr << ex.displayText() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
};