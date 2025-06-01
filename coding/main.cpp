
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
int main(){
    lambdaExamples();
    return 0;
}

