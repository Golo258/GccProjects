

/*----------------- CLASS METHODS  -----------------------*/

#include "NoteManager.hpp"
#include <iostream>

void NoteManager::addNote(const std::string& newNote) {
    if(newNote.length() > 0){
        notes.push_back(newNote);
    }
    else {
        std::cout << "Note is empty or too small " << std::endl;
    }
}
void NoteManager::showNotes() const {
    std::cout << "------------ Notes ------------ " << std::endl;
    for (size_t iter = 0; iter < notes.size(); iter++) {
        std::cout <<  "Note: " <<  iter + 1  << ": " << notes[iter] << std::endl;
    }
}

void NoteManager::clearNotes() {
    notes.clear();
    std::cout << "All notes cleared" << std::endl;
}

