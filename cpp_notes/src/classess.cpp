// =============================
// classes.cpp
// =============================
#include "classess.hpp"
#include <string>
#include <iostream>

/*-------------- DEFINITIONS ----------------------*/

void classes_runner()
{
}

bool Dog::_validate_age(int age) const
{
    if (age < 0 && age > 20)
    {
        throw std::out_of_range(
            "Dog age outt of reasonable bounds (0..20)");
    }
    else
    {
        return true;
    }
}

Dog::Dog(std::string name)
    : _name(name), _age(0)
{
    ++_alive;
}

Dog::Dog(std::string name, int age)
{
    _name = name;
    if (_validate_age(age))
    {
        ++_alive;
    }
}

Dog &Dog::set_name(const std::string &new_name)
{
    _name = new_name;
    return *this; // dziwne podpytac o to
}

Dog &Dog::set_age(int age)
{
    if (_validate_age(age)){
        _age = age;
    }
    return *this;
}

void Dog::bark() const {
    std::cout << _name << " (age " << _age << "): Woof!\n";
}

void Dog::birthday(){
    set_age(_age++);
}

Dog& Dog::rename(std::string new_name){
    return set_name(new_name);
}

int Dog::alive_count() {
    return _alive;
}


bool operator==(const Dog& a, const Dog& b){
    return a._name == b._name && a._age == b._age;
}
