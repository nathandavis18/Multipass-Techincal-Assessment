#pragma once
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using Json = nlohmann::json;
class MyParser abstract
{
protected:
	cpr::Response getUrlResponse(const cpr::Url& url)
	{
		return cpr::Get(url);
	}

	Json loadJsonData(cpr::Response& response)
	{
		return Json::parse(response.text);
	}
};