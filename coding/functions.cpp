#include "headers.hpp" 
#include <iostream>


int substraction(int primary, int secondary) {
    return primary + secondary + 2; 
}

int loopAndStatements(int amount) {
    int age;
    int wrongAgeAmount = 0;
    
    for (int iter = 0; iter < amount; iter++){
        std::cout << "How old are you? \n";
        std::cin >> age;
        if (age >= 18) {
            std::cout << "You have " << age << "ages. You are allowed to drive" << std::endl;
            return wrongAgeAmount;
        }
        else {
            std::cout << "You have " << age << "ages. Its forbiden you to drive" << std::endl;
            wrongAgeAmount++;        
        }
    }
    return wrongAgeAmount;
}