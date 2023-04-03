 // database.cpp

#include "./Database.h"
#include <iostream>

Database::Database(std::string& filename) {
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

int Database::createTables()  {
    const char *sql = "CREATE TABLE IF NOT EXISTS models ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "name TEXT UNIQUE NOT NULL"
                      ");"
                      "CREATE TABLE IF NOT EXISTS vertices ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "model_id INTEGER,"
                      "x REAL,"
                      "y REAL,"
                      "z REAL,"
                      "FOREIGN KEY (model_id) REFERENCES models (id)"
                      ");";

    char *errMsg = nullptr;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "Error creating tables: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return rc;
    }

    return SQLITE_OK;
}




int Database::insertModel( Model &model) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO models (name) VALUES (?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, model.modelName[0].c_str(), -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error inserting model: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return -1;
    }

    int modelID = static_cast<int>(sqlite3_last_insert_rowid(db));
    sqlite3_finalize(stmt);

    // Insert vertices
    sql = "INSERT INTO vertices (model_id, x, y, z) VALUES (?, ?, ?, ?);";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);

    for ( Vertex * verticePointer : model.vertices) {
        Vertex & vertex = (*verticePointer);
        sqlite3_bind_int(stmt, 1, modelID);
        sqlite3_bind_double(stmt, 2, vertex[0]);
        sqlite3_bind_double(stmt, 3, vertex[1]);
        sqlite3_bind_double(stmt, 4, vertex[2]);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            std::cerr << "Error inserting vertex: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            return -1;
        }

        sqlite3_reset(stmt);
    }

    sqlite3_finalize(stmt);
    return modelID;
}
Model Database::getModelByName(std::string &name) {
    Model model;

    sqlite3_stmt *stmt;
    const char *sql = "SELECT id FROM models WHERE name = ?;";

    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);

    int modelID = -1;
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        modelID = sqlite3_column_int(stmt, 0);
        model.modelName.push_back(name);
    } else {
        std::cerr << "Model not found: " << name << std::endl;
        sqlite3_finalize(stmt);
        return model;
    }
    sqlite3_finalize(stmt);

    // Load vertices
    sql = "SELECT x, y, z FROM vertices WHERE model_id = ?;";
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    sqlite3_bind_int(stmt, 1, modelID);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        Vertex vertex;
        vertex.verticeMatrix[0][0] = sqlite3_column_double(stmt, 0);
        vertex.verticeMatrix[1][1] = sqlite3_column_double(stmt, 1);
        vertex.verticeMatrix[2][2] = sqlite3_column_double(stmt, 2);
        Vertex * verticePointer {new Vertex } ; 
        *verticePointer = vertex ; 
        model.vertices.push_back(verticePointer);
    }
    sqlite3_finalize(stmt);
    return model;
}
