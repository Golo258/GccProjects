
#include <iostream>
#include "headers.hpp"
#include <regex>
#include <memory>
#include <array>
#include <tuple>

// przyklad przestrzeni nazw
namespace subG {
    int print(int a, int b){
        return a + b;
    }
}
namespace divG {
    int print(int a, int b){
        return a - b;
    }
}

// przyklad metody statycznej w klasie -- użycie operatora ::
class Engine {
    public:
        static void start(){
            std::cout << "Engine starting " << std::endl;
        }
    
}; 

void showBasicConceptions() {
    std::cout << "Siemano kolano" << std::endl;
    int subName = subG::print(2,2);
    int divName = divG::print(2,4);
    std::cout <<  subName << std::endl;
    std::cout <<  divName << std::endl;
    Engine::start();

    int resolve = substraction(1,2);
    std::cout <<  divName << std::endl;
    int amountOfWrongCountedAge = loopAndStatements(5);
    std::cout <<  "You said less then 18 ages " << amountOfWrongCountedAge << " times. " << std::endl;
}

void showBasicClassesConceptions() {
    
    SimpleUser user;
    user.name = "Grzesiunia";
    user.age = 12;
    user.introduceYourself();
    user.encriptUserPassword();
    std::cout << "Encyrypted password set \n";

    if (user.checkUserQualifications()){
        std::cout << "User qualified.\n";
    }
}
void collectionExamples(){
    showBasicClassesConceptions();
    vectorExplanation();
    mapsExplanation();
    setExplanation();
    queueExplanation();
}

void lambdaExamples(){
    /*
        funkcja anonimowa, nie ma nazwy, można przekazać jako obiekt 
        składania:
        [capture](parametesr) -> return_type { body }

     */
    auto say_hello = []() {
        std::cout << "siemano\n";
    };
    say_hello();

    //  with parameters
    auto add = [](int a, int b){
        return a + b;
    };

    std::cout << "Result " << add(2,2) << " \n";

    // [] - capture list - czyli co chcemy przekazać z zewnątrz
    // opcje [x] - kopia zmiennej, [&x] - referencja
    //  [=]- wszystko kopia, [&] = wszystko referencja
    int multiplier = 2;
    auto multiply= [multiplier](int x) {
        return x * multiplier;
    };
    std::cout << "Multiply result " << multiply(5) << " \n";

    // z sprecyzowaniem typu
    auto sequence = [&](int a, int b) -> int {
        multiplier *= a;
        return a + b * multiplier;  
    };
    std::cout << "Sequence result: " << sequence(2, 3) << "\n";
    std::cout << "Multiplier after sequene: " << multiplier << "\n";
}

enum class TaskStatus {
    Pending,
    InProgress,
    Done,
    Failed
};

void printStatus(TaskStatus status){
    switch(status){
        case TaskStatus::Pending: std::cout << "[Status] Pending\n";break;
        case TaskStatus::InProgress: std::cout << "[Status] InProgress\n";break;
        case TaskStatus::Done: std::cout << "[Status] Done\n";break;
        case TaskStatus::Failed: std::cout << "[Status] Failed\n";break;
    }
}

struct User {
    int id;
    std::string name;
    int age;
    User(int id, std::string name, int age) : id(id), name(name), age(age) {}
    void print(){
        std::cout << "User " << id << ": " << name << " (" << age << " y/o)\n";
    }
};

//  funkcje generyczne
template <typename Type>
void printArray(const Type* array, int size) {
    std::cout << "[ " ; 
    for (int i = 0; i < size; ++i){
        std::cout << array[i] << " ";
    }
    std::cout << "]\n";
}

// klasy generyczne
template <typename Type>
class Box {
    private:
        Type value;
    public:
        Box(Type v) : value(v) {}
        Type get() const {
            return value; 
        }
        void print() const {
            std::cout << "Box holds: " << value << "\n";
        }
};

class DevidingError: public std::exception {
    public:
        const char* what() const noexcept override {
             return "What are you doing ? ";
        }
};

//  try catch throw example
int devide(int a, int b) {
    if (b == 0){
        throw std::invalid_argument("Its fogived to devide by 0");
    }
    return a/b;
}

//  structured bindings:
void structureBindings() {
    // przyklad z mapą
    std::map<std::string, int> people = {
        {"Maya", 24},
        {"Leszek", 56}
    };

    for (const auto& [name, age]: people) {
         std::cout << name << " ma " << age << " lat\n";
    }
}


int main(){
    lambdaExamples();
    TaskStatus ts = TaskStatus::Pending;
    printStatus(ts);
    
    User golo = {1, "Golo", 24};
    golo.print();

    //  unique ptr
    std::unique_ptr<User> us = std::make_unique<User>(1, "Ania", 23);
    us->print(); // uzywane jako zwykly wskaźnik

    // shared ptr - wiecej niż jeden właściciel
    std::shared_ptr<User> shared = std::make_shared<User>(2,"Golo", 12);
    std::shared_ptr<User> secondOwner = shared;
    secondOwner->print();
    
    // funkctiosn template
    int numbs[]  = {12,51,62,73};
    std::string names[] = {"Robert","Alojzy","Waclaw","Marcin"};
    printArray(numbs, 4);
    printArray(names, 4);

    // class templates
    Box<int> intBox(42);
    Box<std::string> strBox("Hello!");
    intBox.print();    // Box holds: 42
    strBox.print();

    // try catch
    try {
        int result = devide(10, 0);
        std::cout << result << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Zły argument: " << e.what() << "\n";
    }
    catch(const DevidingError& ex){
        std::cerr << "Exception " << ex.what() << "occured. \n";
    }

    // structureBindings
    structureBindings();
    tupleExplanation();
    castowanie();
    typowanie();
    statycznosc();
    return 0;
}

