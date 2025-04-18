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
    Database(const std::string& host, const std::string& user, const std::string& password, const std::string& schema);
    void executeAndPrint(const std::string& query);
};