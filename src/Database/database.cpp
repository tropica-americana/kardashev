// database.cpp

#include "./Database.h"
#include <iostream>

Database::Database(const std::string& filename) {
    int rc = sqlite3_open(filename.c_str(), &db);

    if (rc) {
        std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        exit(1);
    }

    createTables();
}

Database::~Database() {
    sqlite3_close(db);
}

int Database::createTables() {
    // Implement the createTables() function here
    
}

int Database::insertModel(const Model& model) {
    // Implement the insertModel() function here
}

Model Database::getModelByName(const std::string& name) {
    // Implement the getModelByName() function here
}
