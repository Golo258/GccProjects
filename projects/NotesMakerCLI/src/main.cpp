
#include "NoteManager.hpp"
#include <iostream>

int main(){
    NoteManager manager;
    std::string output;
    bool isRunning = true;
    while (isRunning) {
        std::cout << "\nCommands: add, show, search, clear, exit\n> ";
        std::cin >> output;
        ManagerChoice choice = stringToEnum(output);
        switch (choice) {
            case ManagerChoice::ADD: {
                std::cin.ignore();
                std::string note;
                std::cout << "Enter note: ";
                std::getline(std::cin, note);
                manager.addNote(note);
                break;
            } 
            case ManagerChoice::SEARCH: {
                std::cin.ignore();
                std::string searchedNote;
                std::cout << "Enter note to search for: ";
                std::getline(std::cin, searchedNote);
                manager.searchNote(searchedNote);
                break;
            }
            case ManagerChoice::SHOW: {
                manager.showNotes();
                break;
            }
            case ManagerChoice::CLEAR: {
                manager.clearNotes();
                break;
            }
            case ManagerChoice::EXIT: {
                std::cout << "Closing program. Bye" << std::endl;
                isRunning = false;
                break;
            }
            
        }
    }

    return 0;
}