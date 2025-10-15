/*============== IMPORTS ======================*/
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

bool SimpleUser::isPasswordStrongEnough(const std::string& pass){
    std::string userPassword = pass.empty() ? this->password : pass;

    std::regex pattern("^(?=.*[A-Za-z])(?=.*\\d).{6,}$");
    return std::regex_match(userPassword, pattern);
}

std::string SimpleUser::encriptUserPassword() {
    MessageManager manager("Enter your password");
    std::string userPass = "";
    while(true){
        userPass = manager.ManageInputMessage();
        if (!isPasswordStrongEnough(userPass)) {
            std::cout << "Password "<< userPass << " is too weak. Check password rules." << std::endl;
            continue;
        }
        else{
            break;
        }
    }
   
    std::string encryptedPass = "";
    for (char c : userPass) {
        encryptedPass += c + 3;
    }

    this->password = encryptedPass;
    std::cout << "Password encrypted and stored successfully.\n";
    return encryptedPass;
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