
/*--------------- DOCUMENTATION -----------------------

    This class is used to declare base types 
    to use in other classes and headers
*/

/*----------------- LIBRARIES -----------------------*/
#pragma once
#include "httplib.h"
#include <iostream>
#include <string>
#include "json.hpp"
#include <fstream>
#include <vector>

/*----------------- VARIABLES -----------------------*/

typedef const httplib::Request& cRequest;
typedef httplib::Response& Response;
typedef nlohmann::json json;

enum class MediaType {
    JSON,
    TEXT,
    HTML,
    YAML
};

inline std::string mediaTypeToString(MediaType type){
    switch (type) {
        case MediaType::JSON: return "application/json";
        case MediaType::TEXT: return "text/plain";
        case MediaType::HTML: return "text/html";
        case MediaType::YAML: return "text/yaml";
        default: return "application/octet-stream";
    }
}