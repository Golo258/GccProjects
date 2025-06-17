/*----------------- LIBRARIES -----------------------*/

#pragma once
#include <vector>
#include <string>
#include <iostream>

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
    friend std::ostream& operator<<(std::ostream& outputStream, const Category& category);

};
typedef const Category& cRefCategory;

struct Note {
    std::string content;
    Category category;

    Note(cRefStr noteContent, cRefCategory noteCategory){
        content = noteContent;
        category = noteCategory;
    }
    friend std::ostream& operator<<(std::ostream& outputStream, const Note& note);
    
};

class NoteManager {
    private: 
        std::vector<Note> notes;
  
    public: 
        void addNote(cRefStr noteContent, cRefCategory noteCategory);
        void showNotes() const; // 
        void clearNotes();  
        void searchNote(std::string patternPart);
};

std::string getUserOutput(std::string message); 