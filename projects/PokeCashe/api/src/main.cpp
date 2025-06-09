/*--------------- DOCUMENTATION -----------------------

    This class is used to:
        - initalize server
        - register routers
        - running the server
*/

/*----------------- LIBRARIES -----------------------*/
#include "httplib.h"
#include "router.hpp"

/*----------------- FUNCTIONS -----------------------*/
int main()
{
    httplib::Server server;
    setup_routes(server);

    std::cout << "Server running on https:localhost:8080" << std::endl;
    server.listen("0.0.0.0", 8080);
    return 0;
}
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/