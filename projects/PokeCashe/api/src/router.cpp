/*--------------- DOCUMENTATION -----------------------

    This class is used to declare the server endpoints
    registration which will be declare and used in .cpp files

*/

/*----------------- LIBRARIES -----------------------*/
#include "include/router.hpp"
#include "include/handlers.hpp"

void setup_routes(httplib::Server &server)
{
    server.Get("/", hello_world);
}

/*----------------- FUNCTIONS -----------------------*/
/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/