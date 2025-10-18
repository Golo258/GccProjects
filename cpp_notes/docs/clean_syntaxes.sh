# ------------Koncepty ------------------
Koncepcja:
    - include/ - deklaracja funckji
    - src/     - implementaja funkcji
    - tests/   - testy funkcjonalności
    - main.cpp - runner wszystkich funkcji
    - CMakeLists.txt | Makefile - kompilacja wszystkich plików
    - dodanie nowego hgeadera/cpp - rebuild i test 
    
Dokumentacja:
    od razu pod/nad implementacą funkcji
    czytelna jasna co sie tam dzieje
        przykłady, tyip
    
# ------------Jak kompilować | budować ------------------

Uruchamianie programów:
    Jak mamy Cmaka to w projekcie robimy
        mkdir build && cd build
        cmake .. - generuje pliki buildowe
        cmake --build . - buduje projekt
        ./main - wykonuje program

# ------------Co robią HPP | CPP------------------
Pliki i używanie ich:
Teoria pliki: 
    .hpp - plik nagłowkowy    
        - mówi "co "funkcje klasy itp"" istnieje
        - piszemy deklaracje bez implementacji
        - jest jak interface (umowa), mówi plikom co mogą wywołać

    .cpp - implemtancja,
        - mówi jak "funkcja, klasa itp" działa
        - definicje, co dokładnie robi funkcja / metoda / klasa
        - silnik pod maską, logika 

# ------------------HPP | CPP------------------
Tworzenie plików nagłowkowych (hpp) | implementacyjnych (cpp)
    w hpp: piszemy same deklaracje funkcji / klas itp
    w cpp: importujemy hpp
        #include "nazwa.hpp"
    i piszemy implementacje do danych rzeczy co są zadeklarowane 

    Przy kompilacji:
        kompiluje main.cpp - wie o Begin::print()
            bo widzi deklaracje w .hpp
        kompiluje plik.cpp - zna definicje Begin::print()
    
    Linker łączy to razem:
        widzi main.cpp wywołuje funkcje, .cpp dostarcza implementacje
            wiec łączy kawąłki razem i daje .exe

    Z reguły w nagłówkach przechowujemy 
        krótki czysty kod 
    A większą logike w .cpp

#---------CMAKE------------
Cmake:
    - jest to generator projektu:
        - czyta CMakeLists.txt
        cd build && cmake ..
        - tworzy pliki konfiguracji budowania
            - tylko raz musi to zrobić ( dopóki struktura projektu sie nie zmieni)
        - uruchamiamy tylko wtedy gdy:
            - dodajemy nowe pliki .cpp
            - zmieniamy CMakeLists.txt
            - kasujemy / zmieniamy / przenosimy coś z projektu
        
        cmake --build .
            - kompilacja (build)
            - bierze wygenerowane przez CMake pliki
            - kompiluje wszystkie .cpp
            - linkuje wynik w psotaci binarki build/main.exe

Syntaxes:
    cmake_minimum_required(VERSION 3.14)
        określa jaką  min wersje c++ używamy
    project(nazwa)
       okresla nazwe projektu
    set(CMAKE_CXX_STANDARD 17)
        ustawia standard C++ dla kompilatora (==-std=c++17.)
    include_directories(include)
        dodaje ścieżki gdzie Cmake ma szukać plików nagłowkowych
        .hpp .h  -- i też biblioteki zewnętrzne(== -Iinclude)
    add_executable(main main.cpp src/namespace_notes.cpp)
        - definicja pliku wykonywalnego
        z tych plików .cpp zbuduj program main
#-----------------------------
Automatyzacja w vs codzie:
    Rozszerzenie CMake Tools
    Select CMakeLists.txt - 
    potem kompilator GC 12.2.0 archlinux
        # jak coś napsujesz to możesz zrobić reconfigure
        # druga opcja w CMake Tools
        
Różnice referencja i pointer:
    referencja - przechowuje adres przypisanego mu obiektu
        - jest jakby aliasem na ten oryginalny obiekt
    
        Musi być od razu zdefiniowana przy deklaracaji:
            - inicjalizacja od razu
            int& number = 12; // od razu przevhowuje adres 12
        Nie można zmienić obiektu przypisanego do referencji
            - nie pozwala zmieniać tego adresu
            int a = 1, b = 2;
            int &ref = a;
            ref = b ; // nie zmieni obiektu tylko jego wartość
                # a = 2 wtedy
        Nie może być nullptr - bo w sumie po co


    Pointer:
        też wskazuje na obiekt jak referencja
        możę być inicjalizowana bez przypisania
            int *ptr; // można jak najbardziej
            lub nullptr
            
        możę zmieniać ten adres
            ptr = &a;
            pr = &b; // zmieniamy obiekt
            

