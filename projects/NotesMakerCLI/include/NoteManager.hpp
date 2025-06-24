/*----------------- LIBRARIES -----------------------*/

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <unordered_map>
#include "json.hpp"
#include "Logger.hpp"
typedef nlohmann::json  json;
/*-----------------  CLASSES -----------------------*/

enum class ManagerChoice {
    ADD,
    SHOW,
    SEARCH,
    CLEAR,
    REMOVE,
    EDIT,
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
        json toJson() const;
        static Category fromJson(const json& j); // metoda należy do klasy nie do obiektu 


    friend std::ostream& operator<<(std::ostream& outputStream, const Category& category);

};
typedef const Category& cRefCategory;

struct Note {
    static int nextId;
    int id;
    std::string content;
    Category category;

    Note() = default; // default konstructor
    Note(cRefStr noteContent, cRefCategory noteCategory){
        id = nextId++;
        content = noteContent;
        category = noteCategory;
    }
    Note(int givenId, cRefStr noteContent, cRefCategory noteCategory){
        id = givenId;
        if (givenId >= nextId){
            nextId = givenId + 1;
        }
        content = noteContent;
        category = noteCategory;
    }
    friend std::ostream& operator<<(std::ostream& outputStream, const Note& note);
    json  toJson() const;
    static Note from_json(const json& j);
};

class NoteManager {
    private: 
        std::vector<Note> notes;
        std::unordered_map<int, Note> noteMap;
    public: 
        NoteManager();
        void addNote(cRefStr noteContent, cRefCategory noteCategory);
        void showNotes() const; // 
        void clearNotes();  
        void searchNote(std::string patternPart);
        void removeNote(int noteId);
        void editNote(int noteId);
};

std::string getUserOutput(std::string message); 
void newThingsToRemember();