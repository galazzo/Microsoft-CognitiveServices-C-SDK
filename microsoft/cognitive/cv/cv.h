#ifndef COGNITIVE_CV
#define COGNITIVE_CV

#include <fstream>
#include <map>

#include <json/json.h>
#include "microsoft/cognitive/cognitive.h"
#include "microsoft/utils/http.h"
#include "microsoft/utils/json_serializable.h"

using namespace std;

namespace Microsoft 
{
    namespace CognitiveServices 
	{
        namespace ComputerVision 
		{
            class Analysis;
            class Description;
            class DomainSpecificContent;			
            struct DomainModel;
            struct Image;
            struct Caption;
            struct Metadata;
            struct Category;
            struct Tag;
            struct Celebrity;
            struct Landmark;
            struct Detail;
			struct Rectangle;
            struct FaceRectangle;
            struct Face;
            struct Color;
            struct ImageType;
            struct Adult;

            namespace Text 
			{
                struct Word;
                struct Line;
                struct Region;
                class RecognitionResult;
                class OcrResult;
                struct OcrSettings;

                HttpResponse RecognizeText(std::string url, ApiServerRegion region, std::string subscriptionKey, std::string ContentType= "application/json");
				HttpResponse RecognizeText(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");

                RecognitionResult RecognizeTextOperationResult(std::string url, std::string subscriptionKey, std::string ContentType="application/octet-stream");

				OcrResult OCR(std::string url, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/json");
                OcrResult OCR(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");				
            }

            namespace PersonGroup
            {
                void Create(HttpContent* data, std::string personGroupId, ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");
                void Train(std::string personGroupId, ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");
                
				namespace Person {
					void Create(HttpContent* data, std::string personGroupId, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");
					void AddFace(HttpContent* data, std::string personGroupId, std::string personId, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");
				}                
            }

			namespace CustomVision 
			{
				class Prediction;
				struct PredictionBox;
				Microsoft::CognitiveServices::ComputerVision::CustomVision::Prediction PredictImage(HttpContent* data, std::string project_id, ApiServerRegion region, std::string predictionKey, std::string ContentType = "application/octet-stream");
				Microsoft::CognitiveServices::ComputerVision::CustomVision::Prediction PredictImageWithNoStore(HttpContent * data, std::string project_id, ApiServerRegion region, std::string predictionKey, std::string ContentType = "application/octet-stream");

				Microsoft::CognitiveServices::ComputerVision::CustomVision::Prediction PredictImageUrl(std::string url, std::string project_id, ApiServerRegion region, std::string predictionKey, std::string ContentType = "application/json");
				Microsoft::CognitiveServices::ComputerVision::CustomVision::Prediction PredictImageUrlWithNoStore(std::string url, std::string project_id, ApiServerRegion region, std::string predictionKey, std::string ContentType = "application/json");
			}

			Analysis Describe(std::string url, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/json");
            Analysis Describe(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");
            
			Analysis Analyze(std::string url, ApiServerRegion region, std::string subscriptionKey, std::string ContentType= "application/json");
			Analysis Analyze(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");

			Analysis Tags(std::string url, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/json");
            Analysis Tags(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");

            Image GenerateThumbnail(std::string url, int width, int height, bool smartCropping, ApiServerRegion region, std::string subscriptionKey, std::string ContentType= "application/json");
			Image GenerateThumbnail(HttpContent* data, int width, int height, bool smartCropping, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");

			DomainSpecificContent RecognizeDomainSpecificContent(std::string url, std::string model, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/json");
            DomainSpecificContent RecognizeDomainSpecificContent(HttpContent* data,  std::string model, ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");
			
            std::vector<DomainModel> DomainSpecificModels(ApiServerRegion region, std::string subscriptionKey, std::string ContentType="application/octet-stream");

            void ToFile(std::string filename, Image& image);
        }
    }
}

struct Microsoft::CognitiveServices::ComputerVision::Image 
{
    char *buffer;
    size_t size;
    std::string content_type;
    int width;
    int height;
};

struct Microsoft::CognitiveServices::ComputerVision::Rectangle 
{
	double left;
	double top;
	double width;
	double height;
};

struct Microsoft::CognitiveServices::ComputerVision::FaceRectangle : Microsoft::CognitiveServices::ComputerVision::Rectangle 
{
    int coveringArea;
};

struct FaceDetectOptions {
	bool returnFaceId;
	bool returnFaceLandmarks;
};

struct Microsoft::CognitiveServices::ComputerVision::Face 
{
    int age;
    std::string gender;
    Microsoft::CognitiveServices::ComputerVision::FaceRectangle position;

	static std::string Identify(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");
	static std::string Verify(HttpContent* data, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");
	static std::string Detect(HttpContent* data, Json::Value& options, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/octet-stream");
	static std::string Detect(std::string url, Json::Value& options, ApiServerRegion region, std::string subscriptionKey, std::string ContentType = "application/json");
};

struct Microsoft::CognitiveServices::ComputerVision::Celebrity 
{
    std::string name;
    double confidence;
    FaceRectangle faceRectangle;
};

struct Microsoft::CognitiveServices::ComputerVision::Landmark
{
    std::string name;
    double confidence;
};

struct Microsoft::CognitiveServices::ComputerVision::Detail 
{
    std::vector<Celebrity> celebrities;
    std::vector<Landmark> landmarks;
};

struct Microsoft::CognitiveServices::ComputerVision::Category 
{
    std::string name;
    double score;
    Detail detail;
};

struct Microsoft::CognitiveServices::ComputerVision::Tag 
{
    std::string name;
    double confidence;
};

struct Microsoft::CognitiveServices::ComputerVision::Color 
{
    std::string dominantColorForeground;
    std::string dominantColorBackground;
    std::vector<std::string> dominantColors;
    std::string accentColor;
    bool isBWImg;
};

struct Microsoft::CognitiveServices::ComputerVision::ImageType
{
    bool clipArtType;
    bool lineDrawingType;
};

struct Microsoft::CognitiveServices::ComputerVision::Adult
{
    bool isAdultContent;
    bool isRacyContent;
    double adultScore;
    double racyScore;
};

struct Microsoft::CognitiveServices::ComputerVision::Caption
{
    std::string text;
    double confidence;
};

struct Microsoft::CognitiveServices::ComputerVision::Metadata
{
    int width;
    int height;
    std::string format;
};

struct Microsoft::CognitiveServices::ComputerVision::DomainModel
{
    std::string name;
    std::vector<std::string> categories;

    void debug();
};


struct Microsoft::CognitiveServices::ComputerVision::Text::Word
{
    Microsoft::CognitiveServices::BoundingBox boundingBox;
    std::string text;
};

struct Microsoft::CognitiveServices::ComputerVision::Text::Line : Microsoft::CognitiveServices::ComputerVision::Text::Word 
{
    std::vector<Microsoft::CognitiveServices::ComputerVision::Text::Word> words;
};

struct Microsoft::CognitiveServices::ComputerVision::Text::Region 
{
    Microsoft::CognitiveServices::BoundingBox boundingBox;
    std::vector<Microsoft::CognitiveServices::ComputerVision::Text::Line> lines;
};

struct Microsoft::CognitiveServices::ComputerVision::CustomVision::PredictionBox 
{
	double propability;
	std::string tagId;
	std::string tagName;
	Microsoft::CognitiveServices::ComputerVision::Rectangle region;
};

#endif
