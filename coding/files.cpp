#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "external/json.hpp"

using json = nlohmann::json;
using namespace std;

void readingSimpleFiles(string fileName) {
    ifstream dataFile(fileName);
    if (!dataFile) {
        cerr << "Cannot open the data.txt file";
    }

    string line;
    while (getline(dataFile, line)) {
        cout << "Loaded line: " << line << endl; 
    }
    dataFile.close();
}

void offStreamFileWriting(string fileName) {
    ofstream writtenDataFile(fileName, ios::app); // append to file

    if (!writtenDataFile) {
        cerr << "Cannot ope the " << fileName << " file to written\n";
    }

    writtenDataFile << "Elegancko ale to idzie\n";
    writtenDataFile << "Jak zle normalnie" << 123 << endl;

    
    //  writting with sstream buffor 
    stringstream stream;
    stream << "O ja cie \n";
    stream << "Ale to jest checa" << endl;
    stream << "ze sie to jeszcze nie wywaliło\n";
    
    writtenDataFile << stream.str();
    writtenDataFile.close();
    cout << "Data has been written to file " << fileName << endl;
}

void writingJsonFile(string fileName) {
    json person;
    person["name"] = "Maciek";
    person["age"] = 54;
    person["isActive"] = true;

    ofstream jsonFile(fileName);
    jsonFile << person.dump(4);
    jsonFile.close();

    cout << "Loaded json file with data\n";
}

void readingFromJsonFile(string  fileName) {
    ifstream jsonFile(fileName);
    json jsonData;
    jsonFile >> jsonData;
    jsonFile.close();

    cout << "Name: " << jsonData["name"] << endl;
    cout << "Age: " << jsonData["age"] << endl;
    cout << "isActive: " << jsonData["isActive"] << endl;
}

void jsonListWriting(string fileName) {
    json persons = json::array();

    persons.push_back({
        {"id", 2},
        {"age", 24},
        {"name", "golo"},
        {"active", true},
    });

    persons.push_back({
        {"id", 3},
        {"name", "Marek"},
        {"age", 45}
    });
    ofstream jsonFile(fileName);
    jsonFile << persons.dump(4);

    jsonFile.close();
}

void jsonListReading(string fileName) {
    ifstream jsonFile(fileName);
    json persons;

    jsonFile >> persons;
    jsonFile.close();

    for (const auto& person: persons) {
        cout << "Person Id: " << person["id"] << "Name: " << person["name"];

        if (person.contains("age")){
             cout << ", age: " << person["age"];
        }

        if (person.contains("active")) {
            cout << ", active: " << (person["active"].get<bool>() ? "yes" : "no");
        }
        cout << endl;
    }

    // other operations
    /*
        contains -- check whether key is in 
        person.value(age, 0) -- loading value with default
        for (auto& [klucz, wartosc] : persons.items())  -- iterating through map
    */
}



int main() {
    string fileName = "static/data.txt";
    string jsonFileName = "static/jsonData.json";
    // readingSimpleFiles(fileName);
    // offStreamFileWriting(fileName);
    // writingJsonFile(jsonFileName);
    // readingFromJsonFile(jsonFileName);
    jsonListWriting(jsonFileName);
    jsonListReading(jsonFileName);
    return 0;
}