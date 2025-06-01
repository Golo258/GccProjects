
/*============== IMPORTS ======================*/
#include "headers.hpp" 
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

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

// Collections

void vectorExplanation(){
    //  jak lista w pythonie, sam zarządza iloścą elementów
    //  dodawanie / usuwanie, automatycznie rośnie 
    std::vector<int> numbers;
    numbers.push_back(10); // dodanie na koniec listy
    numbers.push_back(30);
    std::cout << "By index: " << numbers[0] << "\n"; // 10

    std::cout << "Size: " << numbers.size() << std::endl;

    for (int num : numbers) {
        std::cout << num << "\n";
    }
    // remove last
    numbers.pop_back();
    // wstawianie w środek
    numbers.insert(numbers.begin() + 1, 92); // wolniejsze
    numbers.erase(numbers.begin()); // usuwanie z danej pozycji

    std::reverse(numbers.begin(), numbers.end()); // 

    // szukanie po vektorze
    std::vector<int> nums =  numbers;
    if (std::find(nums.begin(), nums.end(), 42) != nums.end()){
         std::cout << "42 found!\n";
    }
    // sortowanie
    std::sort(nums.begin(), nums.end());
    std::cout << "First one: " << nums.at(0) << std::endl; // index
    numbers.clear(); // czyszczenie

}

void collectionsExamples(){
    // Mapa
    std::map<std::string, int> ages;
    ages["John"] = 20;
    ages["Victor"] = 62;

    for (const auto& pair: ages) {
        std::cout << pair.first << ": " << pair.second << " \n";
    }

}