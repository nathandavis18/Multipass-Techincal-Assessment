#include "ubuntu-parser.hpp"
#include <iostream>

UbuntuParser::UbuntuParser(const cpr::Url& url)
{
	auto response = getUrlResponse(url);
	data = loadJsonData(response);
}

const Json& UbuntuParser::getJsonData()
{
	return data;
}