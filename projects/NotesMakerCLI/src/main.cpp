
#include "NoteManager.hpp"
#include <iostream>

int main(){
    NoteManager manager;
    std::string output;

    while (true) {
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
            case ManagerChoice::SHOW: {
                manager.showNotes();
                break;
            }
            case ManagerChoice::SEARCH: {
                manager.searchNote();
                break;
            }
            case ManagerChoice::CLEAR: {
                manager.clearNotes();
                break;
            }
            case ManagerChoice::EXIT: {
                std::cout << "Closing program. Bye" << std::endl;
                break;
            }
            
        }
    }

    return 0;
}