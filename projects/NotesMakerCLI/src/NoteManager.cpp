

/*----------------- CLASS METHODS  -----------------------*/

#include "NoteManager.hpp"
#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <cctype>


const std::string notesFilePath = "static/saved_notes.txt";
// TODO: dodawanie notatek z daną kategoria
// TODO: usuwanie danej notatki po indexie
Category::Category()
{
    name = "";
    description = "";
}

Category::Category(cRefStr categoryName, cRefStr categoryDescription ){
    name = categoryName;
    description = categoryDescription;
}

void NoteManager::addNote(const std::string& newNote) {
    std::ofstream notesSender(notesFilePath, std::ios::app);
    if(newNote.length() > 0){
        notes.push_back(newNote);
        if (!notesSender) {
            std::cout << "Cannot save note to file named: " << notesFilePath << " probably it doesn't exists";
        }
        else{
            notesSender << newNote << std::endl;
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
        std::cout <<  "Note: " <<  iter + 1  << ": " << notes[iter] << std::endl;
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
        if (std::regex_match(note, pattern)){
            std::cout << "Note: " << note << " is present in notes" << std::endl; 
            isPresent = true;
        }
    }
    if(!isPresent) std::cout << "Word " << patternPart << " is not present in notes\n";
}

