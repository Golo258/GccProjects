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
void hello_world(
    const httplib::Request& request,
    httplib::Response& response
) {
    response.set_content(
        "Hello from C++ learning API",
        "text/plain"
    );
}


/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/