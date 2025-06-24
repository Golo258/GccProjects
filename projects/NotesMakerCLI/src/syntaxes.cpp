
// -makro - mechanizm preprocesora c++
//  przed kompilacją
// ifdef - jesli zmienna jest zdefinoiwana
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstring>

void logMessage(const std::string& msg);

#define RADIUS 5                        // normal var
#define TEST_MODE true                  // normal var
#define SQUARE_FUNC(arg) ((arg * arg))  // function
#ifdef TEST_MODE
#ifndef LOG
#define LOG(msg) std::cout << "[LOG] " << msg << std::endl
#endif
#else
#define LOG(TEST_MODE)
#endif

#define PI_second  3.125
constexpr double PI = 3.14562;
// constexpr -- stała kompilowana 
//  nma ty , jest widoczna w debugrze, 
#define LOG_ERROR(msg) std::cerr << "[ERROR] " << msg << " (" << __FILE__ << ":" << __LINE__ << ")" << std::endl;

// #pragma once // zapobiega wielokrotnego includowaniu nagłowków
// #ifdef, #ifndef, #if, #else, #endif -- warunkowe kompilowanie kodu 

#undef TEST_MODE // zapomina makro 

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

//  ## łączenie nazwa 
//  # zamiana na string
#define UNIQUE_ID(prefix)  int prefix_##__LINE__ // sklei
UNIQUE_ID(tmp); // do generowania zmiennych

//  sprawdzanie typów na etapie kompilacji
static_assert(sizeof(int) == 4, "int musi mieć 4 bajty");

#define TIME_BLOCK_START auto start = std::chrono::high_resolution_clock::now();
#define TIME_BLOCK_END(name) \
    auto end = std::chrono::high_resolution_clock::now(); \
    std::cout << name << " took " \
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() \
              << "ms\n";

int main() {
    LOG("Wynik: " << SQUARE_FUNC(RADIUS));
    // makra debugowe, predefiniowane przez kompilator 
    TIME_BLOCK_START
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    TIME_BLOCK_END("SLEEP BLOCK")

    LOG(__FILE__);
    LOG(__LINE__);
    LOG(__func__);
    LOG(__DATE__); 
    LOG(__TIME__);
    LOG(__FILENAME__);

    //  inne fajne 
    LOG_ERROR("Siemano");
    
}