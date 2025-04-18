#include "Database.h"

Database::Database(const std::string& host, const std::string& user, const std::string& password, const std::string& schema) {
    driver = sql::mysql::get_mysql_driver_instance();
    con.reset(driver->connect(host, user, password));
    con->setSchema(schema);
}

void Database::executeAndPrint(const std::string& query) {
    std::unique_ptr<sql::Statement> stmt(con->createStatement());
    std::unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
    sql::ResultSetMetaData* meta = res->getMetaData();
    int columnCount = meta->getColumnCount();

    // Nagłówki
    for (int i = 1; i <= columnCount; ++i)
        std::cout << meta->getColumnName(i) << " ";
    std::cout << std::endl;

    // Wiersze
    while (res->next()) {
        for (int i = 1; i <= columnCount; ++i)
            std::cout << res->getString(i) << " ";
        std::cout << std::endl;
    }
}