
/*--------------- DOCUMENTATION -----------------------

    This class is used to define database class structure
    and methods which will be used with this database
*/

/*----------------- LIBRARIES -----------------------*/
#include "database.hpp"

/*----------------- FUNCTIONS -----------------------*/
PokeBase::PokeBase(cRefString connectionCredentials,
                   std::string name,
                   std::string type,
                   int level) : conn(connectionCredentials), name(name), type(type), level(level)
{
    if (!conn.is_open())
        throw std::runtime_error("Failed to connect to postgreSQL Database");
    else
        std::cout << "Connected successfully to Database";
}

inline void PokeBase::setName(cRefString newName) { name = newName; }
inline void PokeBase::setType(cRefString newType) { type = newType; }
inline void PokeBase::setLevel(int newLevel) { level = newLevel; }

inline std::string PokeBase::getName() const {return name;}
inline std::string PokeBase::getType() const { return type;}
inline int PokeBase::getLevel() const {return level; }

/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/
/*----------------- VARIABLES -----------------------*/
