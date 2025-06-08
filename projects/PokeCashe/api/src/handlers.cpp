/*--------------- DOCUMENTATION -----------------------

    This class is used to declare the server endpoints
    registration which will be declare and used in .cpp files

*/

/*----------------- LIBRARIES -----------------------*/
#include "handlers.hpp"

/*----------------- VARIABLES -----------------------*/
PokeBase database(
    "dbname=pokedb user=golo password=golo", "default", "normal", 1
);

/*----------------- FUNCTIONS -----------------------*/
/*
    request - informacje o zapytaniu , nagłowki parametry i body
        request.path
        request.method
        request.body
        request.has_param("id")
        request.get-param_value("id")
    response - sutawiamy odpowiedz jaka serwer ma odesłać
    status ocntent typ MIME
*/
void hello_world(cRequest request, Response response)
{
    response.set_content(
        "Hello from C++ learning API",
        mediaTypeToString(MediaType::TEXT)
    );
}
void json_content(cRequest request, Response response)
{
    std::string name = "stranger";
    if(request.has_param("name")){
        name = request.get_param_value("name");
    }

    json responseBody;
    responseBody["message"] = "Hello, " + name;

    response.set_content(
        responseBody.dump(4), 
        mediaTypeToString(MediaType::JSON)
    );
}

void create_table(cRequest request, Response response)
{
    if (!request.has_param("name")) {
        response.status = 400;
        response.set_content(
            "Missing 'name' parameters",
            mediaTypeToString(MediaType::TEXT)
        );
        return;
    }

    std::string tableName = request.get_param_value("name");
    database.initTable(tableName);

    response.set_content(
        "Table " + tableName + " created sucessfully \n",
        mediaTypeToString(MediaType::TEXT)
    );
}

void add_pokemon(cRequest request, Response response)
{
    try{
        if(!database.tableExists("pokemons")){
            response.status = 400;
            response.set_content(
                "Table 'pokemons' doesn't exists. Please create it first",
                mediaTypeToString(MediaType::TEXT)
            );
            return;
        }
        auto body = json::parse(request.body);
        std::string name = body["name"];
        std::string type = body["type"];
        int level = body["level"];
        
        std::string statement = database.prepareStatement();
        database.addPokemon(statement, name, type, level);
        response.set_content(
            "Pokemon " + name + " added successfully \n",
            mediaTypeToString(MediaType::TEXT)
        );
    }
    catch (const std::exception & e) {
        response.status = 400;
        response.set_content(
            std::string("Error: ") + e.what(),
            mediaTypeToString(MediaType::TEXT)
        );
    }
}