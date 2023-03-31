// database.h

#pragma once

#include <string>
#include "../Model/Model.h"
#include <sqlite3.h>

class Database {
public:
    Database(const std::string& filename);
    ~Database();

    int insertModel(const Model& model);
    Model getModelByName(const std::string& name);

private:
    sqlite3* db;
    int createTables();
};
