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
    