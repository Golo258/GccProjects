/*------------------INCLUDES--------------------------*/
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cpr/cpr.h>
#include "lib/json.hpp"
#include <string>

using json = nlohmann::json;
namespace fs = std::filesystem;

/*-----------------GLOBAL VARIABLES--------------------------*/

std::string BASE_URL = "https://pokeapi.co/api/";
std::string JSON_SUFIX = ".json";

/*-----------------FUNCTIONS--------------------------*/
void getRequestData()
{
    std::string name = "pikachu";
    std::string requestURL = BASE_URL + "v2/pokemon/" + name;
    std::string cacheFilePath = "cache/" + name + JSON_SUFIX;

    cpr::Response response = cpr::Get(cpr::Url(requestURL));

    if (response.status_code != 200)
    {
        std::cerr << "Failed to fetch pokemon data: "
            << response.status_code << std::endl;
        exit(0);
    }

    fs::create_directories("cache"); // check whether exists
    std::ofstream pokemonCasheFile(cacheFilePath);
    pokemonCasheFile << response.text;

    pokemonCasheFile.close();
    std::cout << "Pokemon saved to " << cacheFilePath << std::endl;

}
  
/*-------------------INVOKE-------------------------*/

int main()
{
    getRequestData();
    return 0;
}
