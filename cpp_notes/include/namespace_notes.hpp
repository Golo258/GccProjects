
/*-------------- IMPORTS ----------------------*/
#pragma once
#include <iostream>

/*-------------- DECLARATIONS ----------------------*/
/*
    Sposób na grupowanie nazw
        (funkcji, klas, zmienych) w logiczne bloki,
        aby uniknąć konfliktu nazw w projetach
        Dostęp poprzez using nazwa_namespacu
        print() -> funkcja z danego namespacu

    Aby dostać sie potem do funkcji z tego namespacu używamy:
        nazwa_namespacu::funkcja()

    Można stworzyć alias do przestrzeni nazw
        namespace IO = App::IO;
        IO::read();
        
    Można tworzyć anonimowe przestrzenie nazw
        namespace {
            funckja() { deklaracja }
        }
    taka przestrzeń jest static i widoczna tylko w danym .cpp

*/
namespace Begin {
    void print();
}
namespace End {
    void print();
}
/*
    Można tworzyć zagnieżdzone namespacy
        od C++17 można wewnętrzne deklarować jako
        namespace Out::In {}
*/
namespace Out {
    namespace Inner {
        void read();
        void write();
    }
}
// C++17
namespace App::IO {
    void read();
    void write();
}

/*
    Można tworzyć inline namespace
        umożliwia wersjonowanie np API
    API::append_list() # domyślnie V1
    API::v2::append_list() # jawnie v2

    inline daje coś takiego że jest widoczne 
        jakby v1 było bezpośednio w API
    
        wtedy traktuejmy na przykłąd tą wersje v1
            jakby była domyslna/aktualna wersja
        a inne już musimy wymusić

    Nie może być przez to dwóch inner inline namespaców
*/
namespace API {
    inline namespace v1 {
        void append_list();
    }
    namespace v2 {
        void append_list();
    }
}

