#include "microsoft/cognitive/cv/cv.h"
#include "microsoft/utils/json_serializable.h"
#include <map>
#include <iostream>
#include <math.h>

using namespace std;
using namespace Microsoft::CognitiveServices::ComputerVision;

Microsoft::CognitiveServices::ComputerVision::Image Microsoft::CognitiveServices::ComputerVision::GenerateThumbnail(HttpContent* data, int width, int height, bool smartCropping, ApiServerRegion region, std::string subscriptionKey, std::string ContentType)
{
    std::string endpoint = "https://" + ApiServer(region) + "/vision/v2.0/generateThumbnail?width="+std::to_string(width)+"&height="+std::to_string(height)+"&smartCropping=" + ( smartCropping ? "true" : "false");

    Microsoft::CognitiveServices::ComputerVision::Image result;

    std::map<string, string> headers;
    headers.insert(std::pair<std::string, std::string>("Ocp-Apim-Subscription-Key", subscriptionKey));
    headers.insert(std::pair<std::string, std::string>("Content-Type", ContentType));

    HttpResponse response = post(endpoint, "", &headers, data);

    if( response.status == 0)
    {
        result.content_type = response.headers["Content-Type"];
        result.size = std::stoi(response.headers["Content-Length"]);
        result.width = width;
        result.height = height;
        result.buffer = new char[result.size];
        response.content.copy(result.buffer, result.size);
    }

    return result;
}

Microsoft::CognitiveServices::ComputerVision::Image Microsoft::CognitiveServices::ComputerVision::GenerateThumbnail(std::string url, int width, int height, bool smartCropping, ApiServerRegion region, std::string subscriptionKey, std::string ContentType)
{
	std::string endpoint = "https://" + ApiServer(region) + "/vision/v2.0/generateThumbnail?width=" + std::to_string(width) + "&height=" + std::to_string(height) + "&smartCropping=" + (smartCropping ? "true" : "false");

	Microsoft::CognitiveServices::ComputerVision::Image result;

	std::map<string, string> headers;
	headers.insert(std::pair<std::string, std::string>("Ocp-Apim-Subscription-Key", subscriptionKey));
	headers.insert(std::pair<std::string, std::string>("Content-Type", ContentType));

	HttpContent data;
	std::string json = "{\"url\": \"" + url + "\"}";
	data.buffer = new char[json.size() + 1];
	strcpy(data.buffer, json.c_str());
	data.size = json.size() + 1;

	HttpResponse response = post(endpoint, "", &headers, &data);

	if (response.status == 0)
	{
		result.content_type = response.headers["Content-Type"];
		result.size = std::stoi(response.headers["Content-Length"]);
		result.width = width;
		result.height = height;
		result.buffer = new char[result.size];
		response.content.copy(result.buffer, result.size);
	}

	return result;
}