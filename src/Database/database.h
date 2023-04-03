// database.h

#pragma once

#include <string>
#include "../Model/Model.h"
// #include "../libs/sqlite3/sqlite3.h"
#include <sqlite3.h>
class Database {
public:
    Database( std::string& filename);
    ~Database();
    int insertModel( Model& model);
    Model getModelByName( std::string& name);

private:
    sqlite3* db;
    int createTables();
};
