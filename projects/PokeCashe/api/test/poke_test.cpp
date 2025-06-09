
/*--------------- DOCUMENTATION -----------------------

    This class is used to define test cases in order to 
    verify that the endpoint are created correctlly
    and work as it supposed to work
*/

#include <gtest/gtest.h>
#include "../include/database.hpp"

TEST(DatabaseTest, CanCreateAndDetectTable)
{
    PokeBase db("dbname=pokedb user=golo password=golo", "testmon", "fire", 3);
    std::string testTable = "test_table_" + std::to_string(rand() % 10000); 
    EXPECT_FALSE(
        db.tableExists(testTable)
    ) << "Table should not exists before creation";
    
    db.initTable(testTable);

    EXPECT_TRUE(
        db.tableExists(testTable) 
    ) << "Table should exists after creation";
}