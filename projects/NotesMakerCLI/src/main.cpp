
#include "NoteManager.hpp"
#include <iostream>

int main(){
    NoteManager manager;
    std::string command;

    while (true) {
        std::cout << "\nCommands: add, show, clear, exit\n> ";
        std::cin >> command;

        if (command == "add") {
            std::cin.ignore();
            std::string note;
            std::cout << "Enter note: ";
            std::getline(std::cin, note);
            manager.addNote(note);
        } else if (command == "show") {
            manager.showNotes();
        } else if (command == "clear") {
            manager.clearNotes();
        } else if (command == "exit") {
            break;
        } else {
            std::cout << "Unknown command.";
        }
    }

    return 0;
}