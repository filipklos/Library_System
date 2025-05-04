#include "Database.h"

Database::Database(const string& host, const string& user, const string& password, const string& schema)
{
    driver = sql::mysql::get_mysql_driver_instance();
    con.reset(driver->connect(host, user, password));
    con->setSchema(schema);
}

void Database::executeUpdate(const string& query)
{
    auto stmt = unique_ptr<sql::Statement>(con->createStatement());
    stmt->executeUpdate(query);
}

unique_ptr<sql::ResultSet> Database::executeQuery(const string& query)
{
    auto stmt = unique_ptr<sql::Statement>(con->createStatement());
    return unique_ptr<sql::ResultSet>(stmt->executeQuery(query));
}