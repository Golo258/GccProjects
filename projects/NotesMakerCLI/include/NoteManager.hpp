/*----------------- LIBRARIES -----------------------*/

#pragma once
#include <vector>
#include <string>

/*-----------------  CLASSES -----------------------*/

enum class ManagerChoice {
    ADD,
    SHOW,
    SEARCH,
    CLEAR,
    EXIT
};

typedef const std::string& cRefStr; 
ManagerChoice stringToEnum(std::string option);

class Category {
    private:
        std::string name;
        std::string description;
    
    public:
        Category ();
        Category(cRefStr name, cRefStr description);

        inline cRefStr getName() const { return name; };
        inline cRefStr getDescription() const { return description; };

        inline void setName(cRefStr newName) {
            if (newName.length() > 0 )
                name = newName;
            else
                std::cout << "Category name should not be empty";
        };
        inline void setDescription(cRefStr newDescription) {
            if (newDescription.length() > 0 )
                description = newDescription;
            else
                std::cout << "Category description should not be empty";    
        };

};

class NoteManager {
    private: 
        std::vector<std::string> notes;
  
    public: 
        void addNote(const std::string & note);
        void showNotes() const; // 
        void clearNotes();  
        void searchNote(std::string patternPart);
};