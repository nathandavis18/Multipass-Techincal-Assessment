#pragma once
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "myParser.hpp"

class UbuntuParser : public MyParser
{
public:
	UbuntuParser(const cpr::Url& url);
	const Json& getJsonData();
private:
	Json data;
};