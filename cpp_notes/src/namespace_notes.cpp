
#include "namespace_notes.hpp"

namespace Begin {
    void print() {
        std::cout << "Namespace Begin \n";
    }
}

namespace End {
    void print() {
        std::cout << "Namespace End \n";
    }
}

void Out::Inner::read() {
    std::cout << "Reading in Inner\n";
}

void Out::Inner::write() {
    std::cout << "Writing in Inner\n";
}