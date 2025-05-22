
#include <iostream>
#include "headers.hpp"
#include <regex>

/*============== MESSAGE MANAGER ======================*/
MessageManager::MessageManager(): message("Not given messae") {}

MessageManager::MessageManager(std::string message){
    this->message = message;
}

std::string MessageManager::ManageInputMessage(){
    std::cout << this->message << std::endl;
    std::cin >> output;

    return output;
}


/*============== SIMPLE USER ======================*/

void SimpleUser::introduceYourself(){
    std::cout << "Hello my name is " << name 
              << " and i have " << age << " years old\n";  
}

bool SimpleUser::isPasswordStrongEnough(const std::string& password = ""){
    std::string userPassword = password.empty() ? this->password : password;
    
    std::regex pattern(
        "^(?=.*[A-Z])(?=.*\\d)(?=.*[^A-Za-z0-9]).{8,}$"
    );

    return std::regex_match(userPassword, pattern);
}

std::string SimpleUser::encriptUserPassword(){
    MessageManager manager("Enter your password");
    std::string userPass = manager.ManageInputMessage();
    if (!isPasswordStrongEnough(userPass)) {
        std::cout << "Password to weak. Check password rules" << std::endl;
        return;
    }

    
}

bool SimpleUser::checkUserQualifications(){
    return true;
}

/*============== OLD MAN ======================*/
void OldMan::isExperienceAvailable(){
    if(isStillOld){
        yearsOfExperience += 2;
    }
}