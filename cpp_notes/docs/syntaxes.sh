
#--------------------------------------------
# Zagadnienia
- namespace   - przestrzeń nazw -
        służy do grupowania kodu /unkniecie konfliktów
        grupowanie funkcji zmiennych klas i nadanie im unikalnych nazw " imie z prefiksem"
        -- tworzone żeby uniknąc kolizji nazw

        np:
            int print() {
                return 1;
            }

            int print() {
                return 2; // ❌ Błąd! Funkcja już istnieje
            }
        nie może byc takich samych nazw i deklaracji funkcji 
            namespace A {
                int print() {
                    return 1;
                }
            }

            namespace B {
                int print() {
                    return 2;
                }
            }

    skrót do użycia zmiennych nazw bez std:: 
    using namespace dany namespace

    std::cout
        używa obiektu cout z danej przestrzeni


#----------------------------------
Operatory:
    :: -- operator zakresu - scope resolution operator 
        Gdzie używamy:
            - namespaces
                std::cout
            
            - klasy (funkcje statyczne) 
                Klasa::funkcjaStatyczna()

            -- wewntrz metod (indefinicja)
                Klasa::myMethod()

            -- globalny zarkes
                ::main - 


    Operatory_binarne:
    #<< -- przesuniecie bitowe w lewo  x << 2  czyli x * 4 
    #>> -- przesuniecie bitowe w prawo x >> 1  czyli x / 2
        #00011 - 3  << przesuwamy bity w lewo 00110 - 6 czyli razy 2 
        #00110 - 6   >> przesuwamy bity w prawo 00011 - 3  czyli podzieoen przez 2 

    Przeciążanie operatorów:

#----------------------------------
Pliczki:
    .hpp -- pliki nagłowkowe czyli takie ktore
        przechowujaca samą deklaracje funkcji klas struktur typów zmiennych globalnych
            co jest dostepne ale bez okreslenia co robi
    .

#------------------------------
Dyrektywy procesora: # 
    -- to sa komendy dla preprocesora C++, który działą jeszcze zanim program sie kompiluje 
    najważniejsze
        #include --dołącza plik 
        #define - tworzy makro 
        #ifdef -- sprawdzenie czy jest cos zdefinowane #define
        #ifndef -- sprawdza czy nie ma takiej definicji
        #endif - # konczy ifdef ifndef
        #pragma once -- alternatywa dla ifndef -- dodaj ten plik tylko raz
        #undef -- usuwa definicje makra

        #ifdef /ndef -- jesli czegos nie/zdeklarowano to robimy to 
        działanie na poziomie całego projektu, sprawdza czy gdzies to juz nie było zadeklarowane


    Makro
        - zastępowanie tekstu przed kompilacją 
        #define PI 3.14
            zanim kod trafi do kompilatora, każde PI będzie zastąpione 3.14
            rodzaje makr:
                stałe define PI 3.14
                pseudo funkcje -> #define DODAJ(a,b ) ((a) + (b))
                flagi #define dodawanie_hpp -- mówi preporcesorowi że dana rzecz po prostu że makro istnieje 


g++ main.cpp functions.cpp -o main.exe
    linkowanie implementacji interfacu

#-----------------
Klasy
    Specyfikatory dostępu   
        public: wszedzie dostep 
        private : tylko sama klasa, uikrytwa dane 
        protected : sama klasa + pochodne - dziedziczaca klasa ma dostep
    
Konstruktory:
    automatycznie przy utworzeniu obiektu klasy


this -> wskaźnik na obiekt klasy 
    this->message -- odwołujesz sie do atrybutu obiektu klasy
    this->show - odwołujesz sie do metody klasy 

    kiedy używać:
        kiedy na przykłąd mamy setter
        i dajemy tą samą naze parametru co atrybutu i sie robi konflikt, maskuje nam zmienną 


Styl C++:
    Klasy - PascalCase - MessageMenager
    Metody: camelCase - siemanoKolano
    zmienne: camelCase - messageValue
    stałe / makra : UPPER_SNAKE_CASE: MAX_LENGTH
    nazwy plikjów: snake_case  - message_manager.cpp


void f1(std::string s);              // kopia
void f2(std::string& s);             // referencja (ale można zmienić)
void f3(const std::string& s);       // referencja tylko do odczytu ✅



# virutal void execute()
    wirtualna metoda: 
        czyli żę można ją nadpisać w klasach dziedziczących po danej klasie bazowej
            ex: virtual void execute();

                # void execute() override {
                    # std::cout << "Executing special Task\n";
                # }
        
# Gettery w C++:
    odczyt wartości prywantych pól
        int getId() const; -- co to kurwa jest
            to oznacza że metoda nei zmienia obiektu
# Setter w C++:"
    zmiana wartosci prywatnych pól


std::string
    typ złożony (object type)
    kopiowanie jest kosztowne - lepiej zmieniać rzeczywisty obiekt

lista inicjalizacyjna kkonstruktora:
    Task::Task(std::string name, int priority, int duration)
        : id(0), name(name), priority(priority), duration(duration) {}

watki: 
    lekkie wykonanie funckji rownolegle z głownym programem
    
        tworzenie wątków:
            std::thread nazwaWatku(funkcja) -- rozpoczynamy watek i funkcje
            nazwaWatku.join() -- poczekaj az funckja z watku sie skonczy
                -- pauzuje główny watek aż sie ten dany nie skonczy
                

Kolekcje w C++:
    std::
        vector -> dynamiczna lista 
        list - lista 2kierunkowa - 
        dequeue - double ended queue
        queue - kolejka FIFO
        stack - stos LIFO
        priority_queue - kopiec (najpierw najwiekszy)
        map -> posorotwane key -> value 
        unordered_map - jak dict w Pytohnie
        set - zbiór, unikalne
        unordered__set -- to samo co set ale nieupożotkowane

Typy:
    auto: - sam zgaduje typ
    enum - klasa enum
        tworzenie zbioru stałych wartości
            enum class Status {
                Status1, Status2
            };
            Status s = Status::Ready
            #  nie można konwertować do int 

        służy do ograniczenia możliwych stanów/
        czytelności kodui, decydowania w if/switch

    struct - klasy ale wszystko jest publiczne
        szybki lekki kontener na dane

    smart_pointery:
        #include <memory>
        specjalne klasy, automatycznie zwalniająpamiec, gdy sa nie potrzebne
            1. unique_ptr - posiada obiekt na wyłączności, -- jeden właściciel
            2. shared_ptr - dzieli własność miedzy wielui, -- wiele rzeczy korzysta z obiektu
            3. weak_ptr   - nie zwieksza lcizby referencji -- by zapobiec cyklicznym zależnością

                std::make_unique<T>() --tworzenie 
    templaty:
        kod generyczny, jeden kod, ale działą na różnych typach
            funkcje, które działają na wielu typach (np. add, printArray, min, swap)
            klasy, których pola/metody są generyczne (np. Box<T>, Pair<K, V>, Buffer<T>)


            template <typename T> // na funkcje 
            T add(T a, T b) {
                return a + b;
            }

    structure bindings:
        rozpakowywanie obiektów na pojedyncze zmienne

    tuple - jak w pythonie - paczka z różnych elementów


Temat:
    explicit 
        - ochrona przed głupimi konwersjami
            C++ lubi sam konwertować typy, czasami nie porzadzanie
            ex:
            # class Task {
                # public:
                    # explicit Task(int priority) {
                        # std::cout << "Task(prio): " << priority << "\n";
                    # }
                # };
            # run(5);         // ❌ błąd kompilacji
            # run(Task(5));   // ✅ jawna intencja
            Gdy masz 1-argumentowy konstruktor
            Gdy nie chcesz, żeby Twój typ „przypadkiem” powstał z czegoś innego

    try/catch/throw   -- przechwytywanie blędów 
        klasy wyjątkow:
            std::runtime_error
            std::invalid_argument
            std::out_of_range
            std::logic_error
                wszystkie dziedziczą po std::exception

            własne wyjkątki
            exception.what( ) -> odczyt wiadomosc
    
    castowanie:
        c - (typ) zmienna - tak nie robimy
        static_cast<type> (value) - 
            zamiana miedzy typami podstawowymi (int double char)
            rzutowania wskaźników w hierarchii dziedziczenia (w górę)
            wywoływania konstruktorów, np. int -> float

        dynamic_cast<type>(value)
            - tylko dla klas wirtualnych
            - bezpeiczne rzutowanie w dół w dziedzieniu
                z klasy bazowej do pochodnej
                    class Base { virtual void foo() {} };
                    class Derived : public Base {};

                    Base* b = new Derived();
                    Derived* d = dynamic_cast<Derived*>(b); // OK

        reinterpreter_cast -- surowe rzutowanie bitów
        const_cast -- usuwa const ze zmiennej

    Definiowanie typów 
        typedef - alias nazwy typu - skrócona nazwa długiego typu  
            - typedef const unsinged int uint;
                uint x = 5;
            
        using
            - using uint = unsinged int;
            - using StringVec = std::vector<std::string>; 
                template<typename T>
                using Vec = std::vector<T>;

        union:
            - niskopiozmowe - strukutura która przechowuje 
                jedno pole naraz, ale może byc wielu typów
                wszystkie pola dzielą ten sam obszar pamieci
                

        variant 
            -- bezpieczna wersaj union 
            pamieta jaki typ jest aktualnie aktywny


        any  -- trzymam cokolwiek
            - przechowuje dowolny typ 
            - moze byc odczytana przez rzutowanie

    statyczność
        static:
            zmienna - nie znika po wyjsciu z zakresu
            funkcja/metoda-  nie ma dostepu do this -- czyli sie odnosi do klasy nie do obiektu
            pole w klasie - nalezy do klasy, nie do obiektu

            w pliku - ta zmienna ma widocznośc tylko tego pliku

    inline:
        sugestia dla kompilatora, wklej ciało funckji tam gdzie jest wywoływana
        mówi kompilatorowi:
            „Zamiast skakać do tej funkcji — wklej mi jej kod TU, w miejscu użycia.”
            czyli z int x = add(2, 3);
            robi w praktyce;
                int x = 2 + 3;



/*--------------- DOCUMENTATION -----------------------*/
/*----------------- LIBRARIES -----------------------*/
/*----------------- FUNCTIONS -----------------------*/
/*----------------- VARIABLES -----------------------*/
/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/

Czyli tak:
    Cmake jak używać:
        Pomaga ci w zbudowaniu i zlinkowaniu całego projektu

Tworzymy sobie pliczek CMakeLists.txt - 1 w głównym katalogu
    cmake_minum_requirted(VERSION 3.14)
        projekt wymaga co wersji 3.14 conajmniej do budowania 

    project() -- defniujesz nazwe / wersje / jezyk projektu
        np: PokeAi
            VERSION 0.1
            CXX - czyli jezyk to C++

    set(CMAKE_CXX_STANDARD 17) -- ustawiasz jaka wersja c++ ma być

    # ważne
    include_directories() 
        - mówi kompilatorowi żeby szukał nagłowków hpp h w tych katalogach -- nie trzeba pisać w kodzie include/plik.hpp

    add_subdirectory()
        - mowi że w src/ jest inny Cmake z defniicją kompilowania
    

W drugim Cmake:
    on mówi z których plików budujemy aplikacje

    set() - tworzy zmienna o nazwie SOURCES 
        i wrzucaqmy do niej dane pliki 

    add_executable -- tworzy plik wykonynwalny o danej nazwie
        używając danych źródeł


budowanie 
cd build
cmake ..
cmake --build .

// przy każdym dodaniu nowych rzeczy do hpp / cpp
wystarczy cmake --build

przy dodaniu nowych plików i zmianie 
Cmake to robimy jeszcze cmake ..


const na końcu funkcji
np:
    inline int getLevel() const {

    }

oznacza
    że metoda nie zmienia żadnych pól obiektu (jego stanu)
    
    

#  exmaplanation of Makefile
# Tworzymy katalogi, jeśli ich nie ma
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

## bierze wszystkie pliki .cpp
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) 
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
# zamienic .cpp na .o i wpierdol do build

all: $(TARGET)

# żegy zbudować target potrzebuje mieć OBJECTS
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^

# żeby zrobić .o to potrzebuje .cpp
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 	
	$(CXX) $(CXXFLAGS) -c $< -o $@


# flagi dla kompilatora 
# standard c++17 | pokazuj ostrzżenia | dodaj folder include do nagłówków
# gdzie znajduje sie kod 
# build # gdzie wpierdalamy pliki .o
# bin = # miejsce pliku .exe wykonywujacego

# flagi 
# -c -> g++ -c src/main.cpp - skompiluj tylko - compile only
# -o -> g++ -c src/main.cpp -o main.o - zapisz wynik tutaj
# .o - object file, plik obiektowy, skompilowany kod z jednego .cpp
# ale jeszcze nie połaczony w całość


# CXX | i flagi to spoko -o zapisuje do pliku bin
# $^ -- bierze wszystkie zależności żeby zbuidować target czyli OBJECTS
# $@- nazwa celu np/bin/notekeeper
# $< pierwsza zależność
# % - dowolna nazwa 