
#include <iostream>
#include "NoteManager.hpp"


void run_manager() {
    NoteManager manager;
    std::string output;
    bool isRunning = true;
    while (isRunning) {
        std::cout << "\nCommands: add, show, search, remove, edit, clear, exit\n> ";
        std::cin >> output;
        try {
            ManagerChoice choice = stringToEnum(output);
            switch (choice) {
                case ManagerChoice::ADD: {
                    std::cin.ignore();
                    std::string noteContent = getUserOutput("Enter note");
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
                case ManagerChoice::REMOVE: {
                    std::cin.ignore();
                    std::string idToRemoval = getUserOutput("Enter note id to remove: ");
                    std::cout << "ID to removal : " << idToRemoval << std::endl;
                    int convertedId = std::stoi(idToRemoval);
                    manager.removeNote(convertedId);
                    break;
                }
                case ManagerChoice::EDIT: {
                    std::cin.ignore();
                    std::string idToRemoval = getUserOutput("Enter note id to edit: ");
                    std::cout << "ID to removal : " << idToRemoval << std::endl;
                    int convertedId = std::stoi(idToRemoval);
                    manager.editNote(convertedId);
                    break;
                }
                case ManagerChoice::EXIT: {
                    std::cout << "Closing program. Bye" << std::endl;
                    isRunning = false;
                    break;
                }
            }
        } catch (const std::invalid_argument& exception) {
            std::cout << "Wrong input given" << std::endl;
        }
    }
}

int main() {
    std::string name = "Paweł";
    int score = 42;
    NOTE_INFO("User %s scored %d points", name.c_str(), score);
    NOTE_DEBUG("Checking %s at line %d", __FILE__, __LINE__);
    NOTE_ERROR("Could not open file: %s", "config.json");
    return 0;
}