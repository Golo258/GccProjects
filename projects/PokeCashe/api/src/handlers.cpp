/*--------------- DOCUMENTATION -----------------------

    This class is used to declare the server endpoints
    registration which will be declare and used in .cpp files

*/

/*----------------- LIBRARIES -----------------------*/
#include "include/handlers.hpp"

/*----------------- FUNCTIONS -----------------------*/
void hello_world(
    const httplib::Request& request,
    httplib::Response& response
)
{
    response.set_content(
        "Hello from C++ learning API",
        "ext/plain"
    );
}

/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/