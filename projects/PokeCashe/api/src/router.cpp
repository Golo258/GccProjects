/*--------------- DOCUMENTATION -----------------------

    This class is used to declare the server endpoints
    registration which will be declare and used in .cpp files

*/

/*----------------- LIBRARIES -----------------------*/
#include "router.hpp"
#include "handlers.hpp"

/*----------------- FUNCTIONS -----------------------*/
/*

*/
void setup_routes(httplib::Server &server)
{
    server.Get("/", hello_world);
    server.Get("/hello", json_content);
    server.Get("/create-table", create_table);
    server.Get("/add-pokemon", add_pokemon);

    server.Get("/docs", [](cRequest request, Response response){
            std::ifstream indexFile("frontend/index.html");
            std::stringstream buffer;
            buffer << indexFile.rdbuf();
            response.set_content(
                buffer.str(), mediaTypeToString(MediaType::HTML)  
            );
    });
    server.set_mount_point("/docs/static" ,"./frontend");

    server.Get("/openapi.yaml", [](cRequest request, Response response) {
        std::ifstream yamlFile("docs/openapi.yaml");
        if (!yamlFile.is_open()) {
            response.status = 500;
            response.set_content("Failed to open openapi.yaml", "text/plain");
            return;
        }

        std::stringstream buffer;
        buffer << yamlFile.rdbuf();
        response.set_content(
            buffer.str(), mediaTypeToString(MediaType::YAML)
        );
    });

}

/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/