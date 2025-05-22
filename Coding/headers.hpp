#include <iostream>
#include <string>


#ifndef SUBSTRACTING_HPP
#define SUBSTRACTING_HPP

int substraction(int primary, int secondary); // only declaration 

#endif

#ifndef LOOP_STATMENETS
#define LOOP_STATMENETS

int loopAndStatements(int amount);

#endif

#ifndef BASIC_USERCLASSES
#define BASIC_USERCLASSES

class SimpleUser {
    private:
        std::string password;

    protected:
        int yearsOfExperience;
        
    public:
        std::string name;
        int age;
    
    void introduceYourself();
    bool isPasswordStrongEnough(const std::string& pass);
    std::string encriptUserPassword();
    bool checkUserQualifications();
};

#endif

#ifndef BASIC_INHERITED_CLASSES
#define BASIC_INHERITED_CLASSES

class OldMan: public SimpleUser{
    public: 
        bool isStillOld;
        
    void isExperienceAvailable();

};

#endif

#ifndef MESSAGE_ASKING_CLASS
#define MESSAGE_ASKING_CLASS

class MessageManager{
    private:
        std::string message;
        std::string output;
    
    
    public:
        std::string ManageInputMessage();
        MessageManager();
        MessageManager(std::string message);
};
#endif
