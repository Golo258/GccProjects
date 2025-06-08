
/*--------------- DOCUMENTATION -----------------------

    This class is used to declare  how the server
    should behave after user send some request
*/

/*----------------- LIBRARIES -----------------------*/
#pragma once
#include "types.hpp"
#include "database.hpp"

extern PokeBase database;
/*----------------- FUNCTIONS -----------------------*/
void hello_world(cRequest request, Response response);

void json_content(cRequest request, Response response);

void create_table(cRequest request, Response response);

void add_pokemon(cRequest request, Response response);

