
/*--------------- DOCUMENTATION -----------------------

    This class is used to define database class structure
    and methods which will be used with this database
*/

/*----------------- LIBRARIES -----------------------*/
#include "database.hpp"
/*----------------- VARIABLES -----------------------*/
// NONE FOR NOW
/*----------------- CLASS METHODS -----------------------*/
PokeBase::PokeBase(cRefString connectionCredentials,
                   std::string name,
                   std::string type,
                   int level) : connection(connectionCredentials), name(name), type(type), level(level)
{
    if (!connection.is_open())
        throw std::runtime_error("Failed to connect to postgreSQL Database");
    else
        std::cout << "Connected successfully to Database" << std::endl;
}

void PokeBase::executeQuery(cRefString query)
{
    try
    {
        pqxx::work transaction(connection);
        transaction.exec(query);
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

std::string PokeBase::prepareStatement()
{
    connection.prepare("add_pokemon",
                       "INSERT INTO pokemons (name, type,level) VALUES($1, $2, $3)");
    return "add_pokemon";
}
void PokeBase::addPokemon(std::string statement,
                          cRefString name,
                          cRefString type,
                          int level)
{
    try
    {
        pqxx::work transaction(connection);
        transaction.exec_prepared(statement, name, type, level);
        transaction.commit();
        std::cout << "Adding pokemons successfully";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
}

bool PokeBase::tableExists(cRefString tableName)
{
    try{
        pqxx::work transaction(connection);
        pqxx::result result = transaction.exec(
            "SELECT to_regclass('" + tableName + "');"
        );

        if (!result.empty() && !result[0][0].is_null()){
            return true;
        }
    }
    catch(std::exception& ex) {
        std::cerr << "Table existence check failed " << ex.what() << std::endl;
    }
    return false;
}

PokeBase::~PokeBase()
{
    std::cout << "Closing connection. Ending session";
}
