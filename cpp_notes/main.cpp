#include <iostream>
#include "namespaces.hpp"
/* 
    Main function to execute notes functions and classes methods
*/
void namespaces_runner(){
    Begin::print();
    End::print();
    using namespace Begin;
    print();
    Out::Inner::write();
    Out::Inner::read();
    // API::Vector_v1 vector1;
    // API::append_list(vector1);
    // API::v2::append_list();
}

int main(){
    namespaces_runner();
    
    return 0;
}

