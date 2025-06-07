
/*============== IMPORTS ======================*/
#include "headers.hpp" 
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <queue>
#include <array>
#include <tuple>
#include <variant>
#include <any>

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

void mapsExplanation() {
    // unordered_map -- dict w Pythonie key -> value 
    std::unordered_map<std::string, int> ages;
    ages["John"] = 20;
    ages["Victor"] = 62;

    std::cout << "John age: " << ages["John"] << std::endl; // value by key
    // if key exists
    if (ages.count("Victor")){
        std:: cout << "Victor exists in map \n";
    }

    for (const auto& pair: ages) {
        std::cout << pair.first << ": " << pair.second << " \n";
    }
    ages.erase("John"); // removing

}
void setExplanation(){
    // set zbior unilalnych wartosci ( posortowany )
    std::set<int> numbers;
    numbers.insert(5);
    numbers.insert(1);
    numbers.insert(3);
    numbers.insert(5); // ignored- it's already in 
    for (int n : numbers) {
        std::cout << n << "\n";
    }
    // inne funckje 
    /* 
        insert /count /find / erase / size /empty
    */
}

void queueExplanation(){
    // zawsze najwiekszy na przodzie ( posortowany ) 
    // Pod spodem: kopiec binarny (heap)
    std::priority_queue<int> q;

    q.push(5);
    q.push(2);
    q.push(10);

    while (!q.empty()) {
        std::cout << q.top() << "\n"; // zawsze największy
        q.pop();
    }
    //  + array 
    std::array<int, 5> nums = {4, 2, 1, 5, 3};

    std::sort(nums.begin(), nums.end());

    for (int x : nums) {
        std::cout << x << " ";
    }
}

void tupleExplanation(){
    auto tup = std::make_tuple("Siemoa", 31, true); // Tworzenie
    std::tuple<std::string, int, double> t2 = {"Mark", 24, 51}; // trudniejsze

    // dostep do elementów
    std::string name = std::get<0>(t2); // starsze
    auto [tupleName, age, height] = t2;
    std::cout << name << " has " << age << " years old and \n";

    //  pair - tylko dwa elementy
    std::pair<int, std::string> para = {1, "Robert"};
    auto [id, nameOfPair] = para;
}

void castowanie(){
    //  stara wersja C
    int x = 10;
    double d = (double) x; // tak nie robimy

    int iter = 24;
    double floatIter = static_cast<double>(iter);
    char charIter = static_cast<char>(iter);

    // surowe rzutowanie bitów
    int x2 = 5;
    char * point = reinterpret_cast<char *> (&x2); // odczyt bajtów z inta

    // modyfikacja stałej zmiennej
    const int a = 10;
    int&b = const_cast<int &>(a);
    b = 20;
}
template<typename T>
using Vec = std::vector<T>;

union Data {
    int i; 
    float f;
    char str[20];
};

void typowanie(){
    // typedef
    typedef const unsigned int uint;
    typedef std::vector<std::string> stringList;
    uint x = 5;
    stringList names = {"Adam", "Ewa"};

    // using
    // using uint = unsigned int;
    // using StringList = std::vector<std::string>;    

    Vec<int> liczby = {1, 2, 3};        // zamiast std::vector<int>
    Vec<std::string> imiona = {"Ania", "Kuba"};

    Data data;
    data.i = 42;
    std::cout << "int: " << data.i << "\n";
    data.f = 3.14;
    std::cout << "int: " << data.i << "\n"; // bełkot 
    std::cout << "int: " << data.f << "\n"; 

    // Lepsza wersja
    std::variant<int, float, std::string> var2;
    var2 = 42;
    var2 = "siemano";
    std::cout << std::get<std::string>(var2);
    // any 
    std::any numb = 12;
    std::cout << std::any_cast<int>(numb) << std::endl;
    numb = std::string("Cześć!");
    std::cout << std::any_cast<std::string>(numb) << "\n";

}

class StaticTask {
    public:
        static int totalTasks;
        StaticTask() {++totalTasks; }

        //  nie ma dostepu do this 
        static void log(const std::string& message){
             std::cout << "[LOG] " << message << "\n";
        }
};
int StaticTask::totalTasks = 0;

void statycznosc(){
    static int counter = 0; // zachowana wartosc miedzy wywołaniami
    ++counter;
    std::cout << counter << "\n"; 
    StaticTask::log("great message"); // mozna wywołąć bez tworzenia obiektu
}