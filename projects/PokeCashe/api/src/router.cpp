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
}

/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/