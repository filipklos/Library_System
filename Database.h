#pragma once
#include <iostream>
#include <mysql/jdbc.h>
#include <memory>
#include <string>

using namespace std;

class Database {
    sql::mysql::MySQL_Driver* driver;
    unique_ptr<sql::Connection> con;
public:
    Database(const string& host, const string& user, const string& password, const string& schema);
    void executeAndPrint(const string& query);

    void executeUpdate(const string& query);
};