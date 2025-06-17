
#include "NoteManager.hpp"
#include <iostream>

int main(){
    NoteManager manager;
    std::string output;
    bool isRunning = true;
    while (isRunning) {
        std::cout << "\nCommands: add, show, search, clear, exit\n> ";
        std::cin >> output;
        try {
            ManagerChoice choice = stringToEnum(output);
            switch (choice) {
                case ManagerChoice::ADD: {
                    std::cin.ignore();
                    std::string noteContent  = getUserOutput("Enter note");
                    std::string categoryName = getUserOutput("Enter category name");
                    std::string categoryDescription = getUserOutput("Enter category description");
                    
                    manager.addNote(noteContent, Category(categoryName, categoryDescription));
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
        catch(const std::invalid_argument& exception ){
            std::cout << "Wrong input given" << std::endl;
        }
    }

    return 0;
}