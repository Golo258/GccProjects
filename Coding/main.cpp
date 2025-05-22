
#include <iostream>
#include "headers.hpp"
#include <regex>

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

void showClassesConceptions() {
    SimpleUser user;
    user.name = "Grzesiunia";
    user.age = 12;
    user.introduceYourself();
}

int main(){
    MessageManager manager("show me the age: ");

    std::string answer = manager.ManageInputMessage();
    std::cout << "Years: " << answer << std::endl;

    return 0;
}

