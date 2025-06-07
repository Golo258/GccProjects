
/*--------------- DOCUMENTATION -----------------------

    This class is used to declare the server endpoints
    registration which will be declare and used in .cpp files

*/

/*----------------- LIBRARIES -----------------------*/
#pragma once
#include "lib/httplib.h"

void hello_world(
    const httplib::Request& request, 
    httplib::Response& response
);

/*----------------- FUNCTIONS -----------------------*/
/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/