
/*--------------- DOCUMENTATION -----------------------

    This class is used to define database class structure
    and methods which will be used with this database
*/

/*----------------- LIBRARIES -----------------------*/
#pragma once
#include "types.hpp"
#include <pqxx/pqxx>
#include <variant>

/*----------------- VARIABLES -----------------------*/
typedef const std::string& cRefString;
typedef std::variant<int, double, std::string> queryParameter;
typedef std::vector<queryParameter> queryParameters;
/*-----------------  CLASSES -----------------------*/
class PokeBase {
    private:
        pqxx::connection connection; // has to be init 
        std::string name;
        std::string type;
        int level;

    public:
        PokeBase(cRefString connectionCredentials,
                std::string name, 
                std::string type,
                int level
        );
        void executeQuery(cRefString query);
        void initBase();
        void initTable(cRefString tableName);
        std::string prepareStatement();
        void addPokemon(std::string statement,
                        cRefString name,
                        cRefString type,
                        int level);
        bool tableExists(cRefString tableName);
        ~PokeBase();

        // getters
        inline std::string getName() const { return name; }
        inline std::string getType() const { return type; }
        inline int getLevel() const { return level;}

        // setters
        inline void setName(cRefString newName) {name = newName; }
        inline void setType(cRefString newType) {type = newType; }
        inline void setLevel(int newLevel)      {level = newLevel; }
};

