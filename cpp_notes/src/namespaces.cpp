
// src/namespaces.cpp

#include "namespaces.hpp"

/*-------------- DEFINITIONS ----------------------*/
namespace Begin
{
    void print()
    {
        std::cout << "Namespace Begin \n";
    }
}

namespace End
{
    void print()
    {
        std::cout << "Namespace End \n";
    }
}

void Out::Inner::read()
{
    std::cout << "Reading in Inner\n";
}

void Out::Inner::write()
{
    std::cout << "Writing in Inner\n";
}
struct API::Vector_v1
{
    float x;
    float y;
};

void API::append_list(Vector_v1 vector)
{
    std::cout << "Appending to list from inline\n";
}

class API::v2::Vector_v2
{
private:
    float x;
    float y;

public:
    float get_x()
    {
        return x;
    }
    float get_y()
    {
        return y;
    }
};

void API::v2::append_list(Vector_v2 vector)
{
    std::cout << "Appending to list from api v2\n";
    //  TODO: to be done later after learning classes
    // std::cout << "Vector x:" << vector.get_x() << std::endl;
    // std::cout << "Vector y:" << vector.get_y() << std::endl;
}
