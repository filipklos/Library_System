#include "Database.h"

Database::Database(const string& host, const string& user, const string& password, const string& schema) {
    driver = sql::mysql::get_mysql_driver_instance();
    con.reset(driver->connect(host, user, password));
    con->setSchema(schema);
}

void Database::executeAndPrint(const string& query) {
    unique_ptr<sql::Statement> stmt(con->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery(query));
    sql::ResultSetMetaData* meta = res->getMetaData();
    int columnCount = meta->getColumnCount();

    // Nagłówki
    for (int i = 1; i <= columnCount; ++i)
        cout << meta->getColumnName(i) << " ";
    cout << endl;

    // Wiersze
    while (res->next()) {
        for (int i = 1; i <= columnCount; ++i)
            cout << res->getString(i) << " ";
        cout << endl;
    }
}