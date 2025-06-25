// -----------------------------
// Preprocesor i makra w C++
// -----------------------------

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstring>
#include <bits/stdc++.h>
// -----------------------------
// Stałe: #define vs constexpr
// -----------------------------

#define RADIUS 5                         // Makro - stała bez typu (niepolecane w nowoczesnym C++)
#define PI_SECOND 3.125                  // Alternatywne makro stałej
constexpr double PI = 3.14562;           // Stała kompilowana z typem (zalecane)

// -----------------------------
// Funkcje makro i operatory makr
// -----------------------------

#define SQUARE_FUNC(arg) ((arg) * (arg)) // Funkcja makro - zawsze dodawaj nawiasy!

// Łączenie nazw (token pasting)
#define UNIQUE_ID(prefix) int prefix##__LINE__
UNIQUE_ID(tmp);  // wygeneruje np. int tmp42;

// Zamiana na string (stringification)
#define TO_STRING(x) #x

// -----------------------------
// Warunkowe kompilowanie
// -----------------------------

#define TEST_MODE

#ifdef TEST_MODE
    #ifndef LOG
        #define LOG(msg) std::cout << "[LOG] " << msg << std::endl
    #endif
#else
    #define LOG(msg)
#endif

#undef TEST_MODE  // Usuwa definicję makra TEST_MODE

// -----------------------------
// Makra predefiniowane (kompilatorowe)
// -----------------------------

#define LOG_ERROR(msg) std::cerr << "[ERROR] " << msg << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// -----------------------------
// Pomiar czasu wykonania
// -----------------------------

#define TIME_BLOCK_START auto start = std::chrono::high_resolution_clock::now();
#define TIME_BLOCK_END(name) \
    auto end = std::chrono::high_resolution_clock::now(); \
    std::cout << name << " took " \
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() \
              << "ms\n";

// -----------------------------
// Sprawdzenie kompilacyjne
// -----------------------------

static_assert(sizeof(int) == 4, "int musi mieć 4 bajty");

// -----------------------------
// Przestrzenie nazwa -namespacy 
// -----------------------------

namespace math {
    constexpr double nRADIUS = 12.5;

    int square(int radius) {
        return radius * nRADIUS;
    }
    
    int multiply(int principal, int secondary){
        return principal * (secondary * nRADIUS);
    }
}

// typy w namespacach
namespace geometry {
    struct Point {
        int xAxis;
        int yAxis;
    };

    Point makePoint(int x, int y) {
        return Point{x, y};
    }
}

namespace text {

    std::string toUpper(const std::string& message){
        std::string result = message;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
    std::string reverse(const std::string& message){
        std::string result = message;
        std::reverse(result.begin(), result.end());
        return result;
    }
}

enum class HttpResponse: uint16_t {
    CREATED        = 201,
    OK             = 200,
    NOT_AUTHORIZED = 203, 

    BAD_REQUEST    = 400,
    FORBIDDEN      = 403,
    NOT_FOUND      = 404,

};
// -----------------------------
// Funkcja main
// -----------------------------

int main() {
    LOG("Wynik: " << SQUARE_FUNC(RADIUS));

    TIME_BLOCK_START
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    TIME_BLOCK_END("SLEEP BLOCK");

    LOG(__FILE__);       // pełna ścieżka do pliku
    LOG(__LINE__);       // numer linii
    LOG(__func__);       // nazwa funkcji (tutaj: main)
    LOG(__DATE__);       // data kompilacji
    LOG(__TIME__);       // czas kompilacji
    LOG(__FILENAME__);   // tylko nazwa pliku
    LOG(math::square(12));
    geometry::Point point = geometry::makePoint(3,12);
    LOG(point.xAxis + point.yAxis);
    
    HttpResponse response = HttpResponse::BAD_REQUEST;
    uint8_t code = static_cast<uint8_t>(response);
    if (response == HttpResponse::NOT_AUTHORIZED){
        std::cout << "To upper: " << text::toUpper("manana") << std::endl;
        std::cout << "Reversed: " << text::reverse("manana") << std::endl;
    }

}
