#pragma once
#include <mysql/jdbc.h>
#include <memory>
#include <string>

using namespace std;

class Database {
    sql::mysql::MySQL_Driver* driver;
    unique_ptr<sql::Connection> con;
public:
    Database(const string& host, const string& user, const string& password, const string& schema);
    // INSERT/UPDATE/DELETE
    void executeUpdate(const string& query);
    // Pobranie ResultSet
    unique_ptr<sql::ResultSet> executeQuery(const string& query);
    // Ujawnienie połączenia
    sql::Connection* getConnection() const { return con.get(); }
};