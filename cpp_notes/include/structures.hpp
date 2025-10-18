
// include/structures.hpp
/*-------------- IMPORTS ----------------------*/
#pragma once
#include <string>
#include <iostream>

/*-------------- DECLARATIONS ----------------------*/
/*
    DOCUMENTATION:
        struct - grupa zmiennych /funkcji
            która opisuje obiekt logiczny
            mały kontener na dane/mini klasa
            ale z domyślnym dostępem PUBLIC
        składania
            struct Nazwa {
                zmienne
            };
        Waże:
            w .hpp deklarujemy całą strukture
            jakie pola potrzebuje itp, bo to jest typ danych
                i kompilator potrzebuje znać rozmiar tego typu
                żeby móc zarezerwować miejsce na stosie / w macie itp
            w .cpp na przykłąd tylko funkcje struktur
                strucktura::funkcja() {definicja}

        Wykonywanie:
            nazwaStruktury  obiekt{argumenty} -- { } -> klamrowe
*/

struct Person
{
    std::string name;
    int age{};

    void introduce() const; // deklaracja metody (ciało w .cpp)
};

void print_person(const Person &p);

/*
    Zagnieżdżone strukutry
    i tymczasowe struktury /anonimowe
    struct {
        std::string name;
        int score;
    } player{"Bob", 51};
*/
struct Address
{
    std::string city;
    std::string street;
};

struct Citizen
{
    Person person;
    Address address;
    bool isInTown;

    void show_citizen();
};

/*
    ===== Knstruktory w strukturach:
        - automatycznie wykonuje sie przy tworzeniu obiektu
        - inicjalizuje pola struktury

    albo poprzez
        NazwaStruktury(wartosci){
            pole = wartosc
        }
        alboo
        Nazwa (wartosci)
            : pole(wartosc) # i to jest lepsze chyba
            {ciało konstruktora, może b yć puste}

    Lista inicjalizacyjna a ten pierwszy różni sie tym że:
        że w liście pola ą przypisywyna w momencie tworzenia
        a w normalnym dopiero po utworzeniu obiektu

        Domyślkny konstruktor
            Struktura()
                :pole1("domyslna"), pole2(wartosc) {}

    === Destruktory:
        funkcja odpalana gdy obiekt jest niszony
            wychodzi ze scopa- zakresu, lub przez delete
    Skłądania:
        ~Nazwa() {ciało }
*/

struct Product
{
    std::string name;
    int amount;

    Product(std::string p_name, int p_amount)
    {
        name = p_name;
        amount = p_amount;
        std::cout << "Creating product\n";
    }
    ~Product()
    {
        std::cout << "\nDestroying product: " << name << std::endl;
    }
    // albo
    // ~Product() = default; // nic nie robimy
};

/*
    Konstruktor kopiujacy:
        to specjalna funkcja w struktrach
        która tworzy nowy obiekt jako kopie innego

        Person p1{"ALa", 25};
        Prson p2 = p1; // wywołuje sie konstruktor kopiujący

    Kompilator tworzy go automatycznie jeśli nie zdefinujesz swojego

*/
/*
    Operator przypisania:
        generatowany automatycznie
        nie tworzy nowego obiektu
        tylko przypisuje do utworzonego inny obiket
        Person p2;
        p2 = p1;    // tutaj NIE tworzysz nowego obiektu

*/

// Przykłąd implemetacji
struct PersonWithCoping
{
    std::string name;
    int age;
    PersonWithCoping();
    PersonWithCoping(const PersonWithCoping &other)
        : name(other.name), age(other.age)
    {
        std::cout << "Copying constructor called\n";
    }

    PersonWithCoping &operator=(const PersonWithCoping &other)
    {
        name = other.name;
        age = other.age;
        return *this;
    }
};

/*
    Przekazywanie obiektu do funkcji
        normalnego
        przez referencje
        przez wskaźnik
    const klasa&
        - funkcja odczytuje tylko dane
        - bez kopiowania, bezpiecznie
    klasas&
        - funkcja zmienia obiekt
        - dostep do oryginału
    Person *- może mieć nullptr- sprawdzamy brak obiektu
    Person - osobna kopia obikeut, lokalne operacje
*/
void show_by_value(Product product);
void show_by_reference(const Product &product);
Product &change_object_by_reference(Product &product);
Product *change_object_by_pointer(Product *product);
void show_by_pointer(const Product *product);

/*
    Zarzadzanie pamiecia w C++
    stack /heap
        stos
            automatycznie zarzadzany przez program
            zmienne lokalne, normalnie tworzone obiektu
            np: Person p {};
                żyje w aktualnym zakresie - funkcji
                koniec funkcji to znika automatycznie

        sterta
            zarzadzasz sam - przez new //delete
            rzeczy które chcesz żeby żyły dłużej niż 1 funkcja
            np: Person* p = new Prson();
                żyje aż nie wykonamy delete p;

        alokowanie / zwalnianie pamieci
            new /delete
            - wywołanie z new zwraca wskaźnik do
                utworzonego obiektu
            - aby można bylo to zrobić, to musi mieć
                zdefiniowany konstruktor

*/

struct Group
{
    std::string name;
    Product *product; // wskznik na obiekt dynamiczny

    Group(std::string n, std::string product_name)
        : name(n), product(new Product(product_name, 30))
    {
        std::cout << "Group created successfully \n";
    }

    ~Group()
    {
        delete product; // zwalnianie zasobów, wymagane
        std::cout << "Group destroyed\n";
    }
};
