/*--------------- DOCUMENTATION -----------------------

    This class is used to declare the server endpoints
    registration which will be declare and used in .cpp files

*/

/*----------------- LIBRARIES -----------------------*/
#include "handlers.hpp"

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
        mTypeToString(MediaType::TEXT)
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
        mTypeToString(MediaType::JSON)
    );
}

/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/