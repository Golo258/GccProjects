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

ManagerChoice stringToEnum(const std::string& option);

class NoteManager {
    private: 
        std::vector<std::string> notes;
  
    public: 
        void addNote(const std::string & note);
        void showNotes() const; // 
        void clearNotes();  
        void searchNote();
};