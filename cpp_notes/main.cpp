#include <iostream>
#include "namespaces.hpp"
#include "structures.hpp"
#include "classess.hpp"
#include "collections.hpp"
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

void structures_runner(){
    Person person{"John", 24};
    person.introduce();
    print_person(person);
    //  zabawa ze wskaźnikami i referencjami
    
    Person* john_pointer = &person;
    Person& john_reference = person;

    std::cout << "Piter pointer introduce\n";
    john_pointer->name = "Piter";
    john_pointer->introduce();
    
    std::cout << "Piter reference introduce\n";
    john_reference.age = 15;
    john_reference.introduce();
    print_person(john_reference);


    // Nested structures
    Address piterAddress{"Cracow", "Maki"};
    Citizen citizen{person, piterAddress, false};
    citizen.show_citizen();
    citizen.isInTown = true;
    citizen.show_citizen();
    // tymczasowe struktury /anonimowe
    struct {
        std::string name;
        int score;
    } player{"Bob", 51};

    std::cout << player.name << std::endl;

    Product car{"Audi", 5};
    Product second{"BMW", 12};
    show_by_value(car);
    show_by_reference(car);
    show_by_pointer(&car);
    second = change_object_by_reference(car);
    show_by_reference(second);
}

void memory_runner(){
    std::cout<< "\nMemory operation\n";
    Group group{"C++", "Many"};
}

int main(){
    // namespaces_runner();
    // structures_runner();
    // memory_runner();
    classes_runner()
    return 0;
}

