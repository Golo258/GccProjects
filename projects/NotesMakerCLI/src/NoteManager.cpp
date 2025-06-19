

/*----------------- CLASS METHODS  -----------------------*/

#include "NoteManager.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <cctype>


const std::string notesFilePath = "static/saved_notes.txt";
int Note::nextId = 0; // init static structure attrbiut

Category::Category()
{
    name = "";
    description = "";
}

Category::Category(cRefStr categoryName, cRefStr categoryDescription ){
    name = categoryName;
    description = categoryDescription;
}

std::ostream& operator<<(std::ostream& outputStream, cRefCategory category){
    outputStream << "Category: " 
                 << category.getName() << " - "
                 << category.getDescription();
    return outputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Note& note){
    outputStream << "Note: " 
                 << "ID: " << note.id << ": "
                 << "Content:" << note.content << " - "
                 << note.category;
    return outputStream;
}

void NoteManager::addNote(cRefStr noteContent, cRefCategory noteCategory) {
    std::ofstream notesSender(notesFilePath, std::ios::app);
    if(noteContent.length() > 0 
        && !noteCategory.getName().empty()
        && !noteCategory.getDescription().empty()
        )
    {
        notes.emplace_back(noteContent, noteCategory); // create object base on type
        if (!notesSender) {
            std::cout << "Cannot save note to file named: " << notesFilePath << " probably it doesn't exists";
        }
        else{
            notesSender << noteContent << " : " << noteCategory << std::endl;
        }
    }
    else {
        std::cout << "Note is empty or too small " << std::endl;
    }

    notesSender.close();
}

void NoteManager::showNotes() const {
    std::ifstream notesLoader(notesFilePath);
    std::cout << "------------ Notes ------------ " << std::endl;
    for (size_t iter = 0; iter < notes.size(); iter++) {
        std::cout << notes[iter] << std::endl;
    }
    std::cout << "Reading from file " << std::endl;
    if (notesLoader.is_open()) {
        std::string line;
        while (std::getline(notesLoader, line)) {
            std::cout << "File note: " << line << std::endl;
        }
        notesLoader.close();
    }
    else {
        std::cout << "Unable to open file " << notesFilePath << std::endl;
    }
}

ManagerChoice stringToEnum(std::string option) {
    for (char& letter : option) {
        letter = std::toupper(static_cast<unsigned char>(letter));
    }
    if (option == "ADD") return ManagerChoice::ADD;
    if (option == "SHOW") return ManagerChoice::SHOW;
    if (option == "SEARCH") return ManagerChoice::SEARCH;
    if (option == "REMOVE") return ManagerChoice::REMOVE;
    if (option == "CLEAR") return ManagerChoice::CLEAR;
    if (option == "EXIT") return ManagerChoice::EXIT;
    throw std::invalid_argument("Invalid option given");
}

void NoteManager::clearNotes() {
    notes.clear();
    std::cout << "All notes cleared" << std::endl;
    std::ofstream fileCleaner(notesFilePath, std::ofstream::out | std::ofstream::trunc);
    fileCleaner.close();
}

void NoteManager::searchNote(std::string patternPart){
    std::regex pattern(".*"+patternPart + ".*");
    bool isPresent = false;
    for (const auto& note: notes){
        if (std::regex_match(note.content, pattern)){
            std::cout << "Note: " << note << " is present in notes" << std::endl; 
            isPresent = true;
        }
    }
    if(!isPresent) std::cout << "Word " << patternPart << " is not present in notes\n";
}

std::string getUserOutput(std::string message) {
    std::string takenOutput;
    std::cout << message << std::endl;
    std::getline(std::cin, takenOutput);
    return takenOutput;
}

void NoteManager::removeNote(int noteId) {
    notes.erase(
        std::remove_if(notes.begin(), notes.end(),
            [noteId](const Note& note){
                return note.id == noteId;
            }
        ),
        notes.end()
    );
}