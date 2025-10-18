// =============================
// classes.hpp
// =============================

/*-------------- IMPORTS ----------------------*/
#pragma once
#include <iostream>
#include <string>
#include <vector>

/*-------------- DECLARATIONS ----------------------*/

/*
    Klasy:
        domyslnie mają wszystkie pola prywatne private
            w struct - public
        private: - pola widoczne tylko wewnątrz klasy

    Definiowanie klasy:
        class Nazwa{
        };
        pole np int age{0} - domślna wartość atrybutu

    Dog() = default;
        -- domyślny konstruktor
    explicit - zabezpiecza przed niejawnym rzutowaniem
        -- konstruktor x argumentowy
            które zabezpiecza przed niejawną konwersją

    Dog(const Dog& other)=default;
        - konstruktor kopiujący

    Dog& operator=(const Dog&other)
        - operator przypisania

    funkcja const noexcept =
        - funkcja nie zmienia obiektu
        - obiecuje że nie rzuci wyjkątkiem


    static alive:
        - oznacza że należy do klasy, nie do konkretnego obiektu
        - alive(0) -zmiena wspólna dla wszystkich obiektów
    
    friend - przyjaciel klasy,
        możę dostać sie do pól prywatnych
        operator == - pozwala porównywać obiekty
*/
class Dog
{
private:
    std::string _name;
    int _age{0};
    static inline int _alive{0}; // statyczne pole

    bool _validate_age(int age) const; // nie zmienia obiektu

public:
    Dog() = default;                // domyślny
    explicit Dog(std::string name); //
    Dog(std::string, int age);
    explicit Dog(const Dog &other) = default;
    Dog &operator=(const Dog &other) = default;
    ~Dog() = default;

    // Getters
    const std::string &name() const noexcept
    {
        return _name;
    }
    int age() const noexcept
    {
        return _age;
    }
    // Settery
    Dog &set_name(const std::string &new_name);
    Dog &set_age(int new_age);

    // Metody
    void bark() const;
    void birthday();
    Dog &rename(std::string new_name);

    // Statyczne
    static int alive_count();

    // przyjaciele
    friend bool operator==(const Dog &a, const Dog &b);
};

/*
    Przykłąd kopmozycji
        jedna klasa zawiera inne obiekty innej klasy

    Kernel add - kopiuje obiekt do wetkora
*/
class Kennel
{
private:
    std::vector<Dog> _dogs;

public:
    Kennel() = default;
    Kennel &add(const Dog &new_dog);
    Kennel &add(Dog &&dog); // przeniesienie
    Kennel &emplace(std::string name, int age);

    void list() const;
    bool contains_name(const std::string &name) const;
};

void classes_runner();