#include <iostream>
#include "namespace_notes.hpp"
/* 
    Main function to execute notes functions and classes methods
*/
void namespace_playground(){
    Begin::print();
    End::print();
    using namespace Begin;
    print();
}

int main(){
    namespace_playground();
    return 0;
}