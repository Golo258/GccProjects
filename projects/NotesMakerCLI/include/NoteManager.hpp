/*----------------- LIBRARIES -----------------------*/

#pragma once
#include <vector>
#include <string>

/*-----------------  CLASSES -----------------------*/

class NoteManager {
    private: 
        std::vector<std::string> notes;
  
    public: 
        void addNote(const std::string & note);
        void showNotes() const; // 
        void clearNotes();

};