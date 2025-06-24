

/*----------------- CLASS METHODS  -----------------------*/

#include "NoteManager.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <regex>

// TODO: opcja edytowania notatki wzgledem ID
// TODO: zmiana struktury danych z vectora na Mape<int ,Note>
// TODO: dodanie Unit Testów do programu, coś innego niż te google test możę
// TODO: dodanie loggera zamiast std:cout
// TODO: dodanie daty i godziny do notatki <ctime>

const std::string notesFilePath = "static/saved_notes.txt";
const std::string notesJsonPath = "static/saved_notes.json";
int Note::nextId = 0;  // init static structure attrbiut

Category::Category() {
    name = "";
    description = "";
}

Category::Category(cRefStr categoryName, cRefStr categoryDescription) {
    name = categoryName;
    description = categoryDescription;
}

json Category::toJson() const {
    return json{{"name", name}, {"description", description}};
}

Category Category::fromJson(const json& j) {
    return Category(j.at("name"), j.at("description"));
}

std::ostream& operator<<(std::ostream& outputStream, cRefCategory category) {
    outputStream << "Category: " << category.getName() << " - " << category.getDescription();
    return outputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Note& note) {
    outputStream << "Note: "
                 << "ID: " << note.id << ": "
                 << "Content:" << note.content << " - " << note.category;
    return outputStream;
}

json Note::toJson() const {
    return json{
        {"id", id},
        {"content", content},
        {"category", category.toJson()},
    };
}

Note Note::from_json(const json& j) {
    return Note(j.at("id").get<int>(), j.at("content"), Category::fromJson(j.at("category")));
}

NoteManager::NoteManager() {
    std::ifstream savedJsonNotes(notesJsonPath);
    if (!savedJsonNotes.is_open()) {
        std::cout << "No saved jSon notes found in files" << std::endl;
        return;
    }

    json jsonNotes;
    savedJsonNotes >> jsonNotes;
    savedJsonNotes.close();

    for (const auto& jsonNote : jsonNotes) {
        Note savedNote = Note::from_json(jsonNote);
        notes.push_back(savedNote);
        noteMap[savedNote.id] = savedNote;

        if (savedNote.id >= Note::nextId) {
            Note::nextId = savedNote.id + 1;
        }
    }
}

void NoteManager::addNote(cRefStr noteContent, cRefCategory noteCategory) {
    std::ofstream notesSender(notesFilePath, std::ios::app);
    if (noteContent.length() > 0 && !noteCategory.getName().empty() && !noteCategory.getDescription().empty()) {
        Note newNote(noteContent, noteCategory);
        notes.push_back(newNote);  // create object base on type
        noteMap[newNote.id] = newNote;
        json jsoNote = newNote.toJson();
        std::ifstream currentNotesFile(notesJsonPath);
        json allNotes;
        if (currentNotesFile.is_open()) {
            currentNotesFile >> allNotes;
            currentNotesFile.close();
        }
        allNotes.push_back(jsoNote);
        std::ofstream jsonNotes(notesJsonPath);
        if (jsonNotes.is_open()) {
            jsonNotes << allNotes.dump(4);
            jsonNotes.close();
        }
        if (!notesSender) {
            std::cout << "Cannot save note to file named: " << notesFilePath << " probably it doesn't exists";
        } else {
            notesSender << noteContent << " : " << noteCategory << std::endl;
        }
    } else {
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
    } else {
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
    if (option == "EDIT") return ManagerChoice::EDIT;
    if (option == "EXIT") return ManagerChoice::EXIT;
    throw std::invalid_argument("Invalid option given");
}

void NoteManager::clearNotes() {
    notes.clear();
    std::cout << "All notes cleared" << std::endl;
    std::ofstream fileCleaner(notesFilePath, std::ofstream::out | std::ofstream::trunc);
    fileCleaner.close();
}

void NoteManager::searchNote(std::string patternPart) {
    std::regex pattern(".*" + patternPart + ".*");
    bool isPresent = false;
    for (const auto& note : notes) {
        if (std::regex_match(note.content, pattern)) {
            std::cout << "Note: " << note << " is present in notes" << std::endl;
            isPresent = true;
        }
    }
    if (!isPresent) std::cout << "Word " << patternPart << " is not present in notes\n";
}

std::string getUserOutput(std::string message) {
    std::string takenOutput;
    std::cout << message << std::endl;
    std::getline(std::cin, takenOutput);
    return takenOutput;
}

void NoteManager::removeNote(int noteId) {
    notes.erase(std::remove_if(notes.begin(), notes.end(), [noteId](const Note& note) { return note.id == noteId; }),
                notes.end());
    noteMap.erase(noteId);
}

// TODO: finish implementing this
void NoteManager::editNote(int noteToEditId) {
    for (Note& note : notes) {
        if (note.id == noteToEditId) {
            std::cout << "Current note" << note << std::endl;
            std::string newContent = getUserOutput("Enter new content");
            std::string newCategoryName = getUserOutput("Enter new category name (leave empty to keep current): ");
            std::string newCategoryDescription =
                getUserOutput("Enter new category description (leave empty to keep current): ");

            if (!newContent.empty()) note.content = newContent;
            if (!newCategoryName.empty()) note.category.setName(newCategoryName);
            if (!newCategoryDescription.empty()) note.category.setDescription(newCategoryDescription);

            noteMap[note.id] = note;

            json updatedJson = json::array();
            for (const Note& note : notes) {
                updatedJson.push_back(note.toJson());
            }

            std::ofstream jsonFile(notesJsonPath);
            jsonFile << updatedJson.dump(4);
            jsonFile.close();
            std::cout << "Note updated" << std::endl;
            return;
        }
    }
    std::cout << "Note with id: " << noteToEditId << "not found" << std::endl;
}

void newThingsToRemember() {
    // input file -- wejśćie - czyli do czytania
    std::ifstream inputFile(notesFilePath);
    // output file - wyjśćie, czyli do pisania
    std::string fileData;
    if (inputFile.is_open()) {
        inputFile >> fileData;  // z plik --> do zmiennej
        inputFile.close();
    }
    std::ofstream outputFile(notesFilePath);
    if (outputFile.is_open()) {
        outputFile << "Something new";  // pliczek <--- jakies rzeczy
        outputFile.close();
    }
}