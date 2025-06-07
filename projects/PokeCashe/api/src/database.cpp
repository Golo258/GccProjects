
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
                   int level) : connection(connectionCredentials), name(name), type(type), level(level)
{
    if (!connection.is_open())
        throw std::runtime_error("Failed to connect to postgreSQL Database");
    else
        std::cout << "Connected successfully to Database";
}

inline void PokeBase::setName(cRefString newName) { name = newName; }
inline void PokeBase::setType(cRefString newType) { type = newType; }
inline void PokeBase::setLevel(int newLevel) { level = newLevel; }

inline std::string PokeBase::getName() const { return name; }
inline std::string PokeBase::getType() const { return type; }
inline int PokeBase::getLevel() const { return level; }

void PokeBase::executeQuery(cRefString query, queryParameters& parameters)
{
    try
    {
        pqxx::work transaction(connection);
        if(parameters.empty()){
            transaction.exec(query);
        }
        else{
            
            transaction.exec_prepared(query, );
        }
        transaction.commit();

        std::cout << "Query executed successfully" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fetching query failed: " << e.what() << std::endl;
    }
}

void PokeBase::initBase()
{
    executeQuery(
        "CREATE DATABASE pokeapi OWNER golo;");
}

void PokeBase::initTable(cRefString tableName)
{
    std::string query =
        "CREATE TABLE IF NOT EXISTS " + tableName +
        "("
        "id SERIAL PRIMARY KEY, "
        "name VARCHAR(60) NOT NULL, "
        "type VARCHAR(30) NOT NULL, "
        "level INTEGER NOT NULL DEFAULT 1"
        ");";

    executeQuery(query);
}

void PokeBase::addPokemon(cRefString name,
                          cRefString type,
                          int level)
{

}

/*-----------------  CLASSES -----------------------*/
/*-----------------  INVOKE -----------------------*/
/*----------------- VARIABLES -----------------------*/
