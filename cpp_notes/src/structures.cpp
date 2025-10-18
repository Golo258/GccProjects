
// src/structures.cpp
#include "structures.hpp"
#include <string>
#include <iostream>

/*-------------- DEFINITIONS ----------------------*/

void Person::introduce() const
{
    std::cout << "Hi, I'm " << name << ". Age: " << age << " .\n";
}
void print_person(const Person &person)
{
    std::cout << person.name << ", " << person.age << std::endl;
}

void Citizen::show_citizen()
{
    if (isInTown)
    {
        person.introduce();
    }
    else
    {
        std::cout << "Citizen " << person.name << " is not in town \n";
    }
}

// przekazywany przez wartość (kopiuje ten obiekt)
void show_by_value(Product product)
{
    std::cout << "By value: " << product.name << std::endl;
}

// przekazywany przez referencje ( nie kopiuje)
void show_by_reference(const Product &product)
{
    std::cout << "By reference: " << product.name << std::endl;
}

// przekazany przez waskźnik (nie kopiuje trzeba sprawdzić nullptr)
void show_by_pointer(const Product *product)
{
    if (product)
    {
        std::cout << "By pointer: " << product->name << std::endl;
    }
    else
    {
        std::cout << "Passed product is null\n";
    }
}

// zwracamy adres/ referencje a nie kopie obiektu zmienionego
Product &change_object_by_reference(Product &product)
{
    product.name = "different";
    return product;
}

Product *change_object_by_pointer(Product *product)
{
    if (!product)
        return nullptr; // zawsze sprawdź
    product->name = "krzysiek";
    return product; // zwracasz ten SAM wskaźnik
}
