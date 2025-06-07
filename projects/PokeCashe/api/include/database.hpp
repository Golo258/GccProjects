
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
/*----------------- FUNCTIONS -----------------------*/

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
        void executeQuery(cRefString query, queryParameters& parameters = {});
        void initBase();
        void initTable(cRefString tableName);
        void addPokemon(cRefString name,
                        cRefString type,
                        int level);
        ~PokeBase();

        // getters
        std::string getName() const;
        std::string getType() const;
        int getLevel() const;

        // setters
        void setName(cRefString newName);
        void setType(cRefString newType);
        void setLevel(int newLevel);
};

/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/
